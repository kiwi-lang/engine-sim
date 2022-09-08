#include "../include/compiler.h"
#include <iostream>

es_script::Compiler::Output *es_script::Compiler::s_output = nullptr;

es_script::Compiler::Compiler(FILE *File)
{
    m_compiler = nullptr;
    LogFile = File;
}

es_script::Compiler::~Compiler()
{
    assert(m_compiler == nullptr);
}

es_script::Compiler::Output *es_script::Compiler::output()
{
    static Output out;
    return &out;
}

// Rules are buggy af
es_script::LanguageRules& es_script::GetRules() {
    static es_script::LanguageRules Rules;
    return Rules;
}

void es_script::Compiler::initialize()
{
    std::vector<std::string> Paths;

    Paths.push_back("../../es/");
    Paths.push_back("../es/");
    Paths.push_back("es/");
    Paths.push_back("E:/engine-sim-sup/Build/bin/Debug/es/");

    initialize(Paths);
}

void es_script::Compiler::initialize(std::vector<std::string> const &SearchPaths)
{
    m_compiler = new piranha::Compiler(&GetRules());
    m_compiler->setFileExtension(".mr");

    for (auto &path : SearchPaths)
    {
        m_compiler->addSearchPath(path);
    }

    GetRules().initialize();
}

bool es_script::Compiler::compile_script(const char *InlineScript)
{
    bool successful = false;

    piranha::IrCompilationUnit *unit = m_compiler->compile_script(InlineScript);

    if (unit == nullptr && LogFile)
    {
        fprintf(LogFile, "Could not process the inline script\n");
    }
    else
    {
        const piranha::ErrorList *errors = m_compiler->getErrorList();
        if (errors->getErrorCount() == 0)
        {
            unit->build(&m_program);

            m_program.initialize();

            successful = true;
        }
        else
        {
            for (int i = 0; i < errors->getErrorCount(); ++i)
            {
                printError(errors->getCompilationError(i));
            }
        }
    }

    return successful;
}

bool es_script::Compiler::compile(const piranha::IrPath &path)
{
    bool successful = false;

    piranha::IrCompilationUnit *unit = m_compiler->compile(path);
    if (unit == nullptr)
    {
        fprintf(LogFile, "Can't find file: %s\n", path.toString().c_str());
    }
    else
    {
        const piranha::ErrorList *errors = m_compiler->getErrorList();
        if (errors->getErrorCount() == 0)
        {
            unit->build(&m_program);

            m_program.initialize();

            successful = true;
        }
        else
        {
            for (int i = 0; i < errors->getErrorCount(); ++i)
            {
                printError(errors->getCompilationError(i));
            }
        }
    }

    return successful;
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

void es_script::Compiler::printError(
    const piranha::CompilationError *err) const
{
    if (!LogFile)
        return;

    const piranha::ErrorCode_struct &errorCode = err->getErrorCode();

    fprintf(LogFile, //
            "%s (%d): error: %s%s: %s\n",
            err->getCompilationUnit()->getPath().getStem().c_str(),
            err->getErrorLocation()->lineStart,
            errorCode.stage.c_str(),
            errorCode.code.c_str(),
            errorCode.info.c_str()
            //
    );

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

            fprintf(LogFile, //
                    "      While instantiating:  %s (%d): %s\n",
                    instance->getParentUnit()->getPath().getStem(),
                    instance->getSummaryToken()->lineStart,
                    formattedName
                    //
            );
        }

        context = context->getParent();
    }
}
