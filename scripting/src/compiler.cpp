#include "../include/compiler.h"

#include <iostream>

es_script::Compiler::Output *es_script::Compiler::s_output = nullptr;

es_script::Compiler::Compiler()
{
    m_compiler = nullptr;
}

es_script::Compiler::~Compiler()
{
    assert(m_compiler == nullptr);
}

es_script::LanguageRules &GetRules()
{
    static es_script::LanguageRules m_rules;
    return m_rules;
}

es_script::Compiler::Output *es_script::Compiler::output()
{
    if (s_output == nullptr)
    {
        s_output = new Output;
    }

    return s_output;
}

void es_script::Compiler::initialize()
{
    m_compiler = new piranha::Compiler(&GetRules());
    m_compiler->setFileExtension(".mr");

    m_compiler->addSearchPath("../../es/");
    m_compiler->addSearchPath("../es/");
    m_compiler->addSearchPath("es/");

    GetRules().initialize();
}

void es_script::Compiler::initialize(std::vector<std::string> &paths)
{
    m_compiler = new piranha::Compiler(&GetRules());
    m_compiler->setFileExtension(".mr");

    /*
    m_compiler->addSearchPath("../../es/");
    m_compiler->addSearchPath("../es/");
    m_compiler->addSearchPath("es/");
    */

    //*
    for (auto &path : paths)
    {
        m_compiler->addSearchPath(path.c_str());
    }
    //*/

    GetRules().initialize();
}

bool es_script::Compiler::compile_script(std::string const& script, const piranha::IrPath &root) {
    piranha::IrCompilationUnit *unit = m_compiler->compile_script(script, root);
    const piranha::ErrorList *errors = m_compiler->getErrorList();

    if (unit != nullptr && errors->getErrorCount() == 0)
    {
        unit->build(&m_program);

        m_program.initialize();

        return true;
    }

    return false;
}

bool es_script::Compiler::compile(const piranha::IrPath &path)
{
    piranha::IrCompilationUnit *unit = m_compiler->compile(path);
    const piranha::ErrorList *errors = m_compiler->getErrorList();

    if (unit != nullptr && errors->getErrorCount() == 0)
    {
        unit->build(&m_program);

        m_program.initialize();

        return true;
    }

    return false;
}

es_script::Compiler::Output es_script::Compiler::execute()
{
    const bool result = m_program.execute();

    if (!result)
    {
        // Todo: Runtime error
    }

    return *output();
}

void es_script::Compiler::destroy()
{
    m_program.free();
    m_compiler->free();

    delete m_compiler;
    m_compiler = nullptr;
}

void es_script::Compiler::dumpErrors(std::function<void(std::string const&)> fun) {
    const piranha::ErrorList *errors = m_compiler->getErrorList();

    for (int i = 0; i < errors->getErrorCount(); ++i)
    {
        fun(dumpError(errors->getCompilationError(i)));
    }
}

 std::string es_script::Compiler::dumpError(const piranha::CompilationError *err) {
    std::stringstream ss;
    printError(err, ss);
    return ss.str();
 }

void es_script::Compiler::printError(
    const piranha::CompilationError *err,
    std::ostream &file) const
{
    const piranha::ErrorCode_struct &errorCode = err->getErrorCode();
    file << err->getCompilationUnit()->getPath().getStem()
         << "(" << err->getErrorLocation()->lineStart << "): error "
         << errorCode.stage << errorCode.code << ": " << errorCode.info << std::endl;

    piranha::IrContextTree *context = err->getInstantiation();
    while (context != nullptr)
    {
        piranha::IrNode *instance = context->getContext();
        if (instance != nullptr)
        {
            const std::string instanceName = instance->getName();
            const std::string definitionName = (instance->getDefinition() != nullptr)
                                                   ? instance->getDefinition()->getName()
                                                   : "<Type Error>";
            const std::string formattedName = (instanceName.empty())
                                                  ? "<unnamed> " + definitionName
                                                  : instanceName + " " + definitionName;

            file
                << "       While instantiating: "
                << instance->getParentUnit()->getPath().getStem()
                << "(" << instance->getSummaryToken()->lineStart << "): "
                << formattedName << std::endl;
        }

        context = context->getParent();
    }
}
