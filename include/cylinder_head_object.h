#ifndef ATG_ENGINE_SIM_CYLINDER_HEAD_OBJECT_H
#define ATG_ENGINE_SIM_CYLINDER_HEAD_OBJECT_H

#include "simulation_object.h"

#include "cylinder_head.h"
#include "geometry_generator.h"
#include "engine.h"

class CylinderHeadObject : public SimulationObject {
    public:
        CylinderHeadObject();
        virtual ~CylinderHeadObject();

#ifdef SIMULATION_RENDERING
        virtual void generateGeometry();
        virtual void render(const ViewParameters *view);
#endif
        virtual void process(float dt);
        virtual void destroy();

        CylinderHead *m_head;
        Engine *m_engine;

    protected:
        void generateCamshaft(
            Camshaft *camshaft,
            double padding,
            double rollerRadius,
            GeometryGenerator::GeometryIndices *indices);
};

#endif /* ATG_ENGINE_SIM_CYLINDER_HEAD_OBJECT_H */
