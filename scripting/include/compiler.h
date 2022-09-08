#ifndef ATG_ENGINE_SIM_COMPILER_H
#define ATG_ENGINE_SIM_COMPILER_H

#include "language_rules.h"

#include "engine_sim.h"
#include "piranha.h"

#include <vector>

namespace es_script
{


    LanguageRules& GetRules();

    class Compiler
    {
    public:
        struct Output
        {
            Engine *engine = nullptr;
            Vehicle *vehicle = nullptr;
            Transmission *transmission = nullptr;
            Simulator::Parameters simulatorParameters;
            ApplicationSettings applicationSettings;

            std::vector<Function *> functions;
        };

    private:
        static Output *s_output;

    public:
        Compiler(FILE *File);
        ~Compiler();

        static Output *output();

        void initialize();
        void initialize(std::vector<std::string> const &SearchPaths);

        bool compile(const piranha::IrPath &path);
        bool compile_script(const char *InlineScript);

        Output execute();
        void destroy();

    private:
        void printError(const piranha::CompilationError *err) const;

    private:
        piranha::Compiler *m_compiler;
        piranha::NodeProgram m_program;
        FILE *LogFile;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_COMPILER_H */