#ifndef ATG_ENGINE_SIM_COMPILER_H
#define ATG_ENGINE_SIM_COMPILER_H

#include "language_rules.h"

#include "engine_sim.h"
#include "piranha.h"

#include <vector>

namespace es_script
{

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
        Compiler();
        ~Compiler();

        static Output *output();

        void initialize();
        void initialize(std::vector<std::string> &paths);

        bool compile(const piranha::IrPath &path);
        Output execute();
        void destroy();

    private:
        void printError(const piranha::CompilationError *err, std::ostream &file) const;

    private:
        piranha::Compiler *m_compiler;
        piranha::NodeProgram m_program;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_COMPILER_H */