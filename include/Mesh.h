#ifndef __MESH_H__
#define __MESH_H__

#include "Float3.h"

#include <vector>

namespace cpom
{

/// Type holding the vertex ids that form a mesh face.
struct Face
{
    /// Vector holding the indices in a list a vertex.
	std::vector<int> vertexIds;
};

/// Interface of Mesh required by cpom.
class Mesh
{
public:
    /// Fill a vector with all vertices in the mesh.
    virtual void getVertices(std::vector<Point> &vertices) const = 0;

    /// Fill a vector with all faces in the mesh.
    virtual void getFaces(std::vector<Face> &faces) const = 0;
};

}

#endif // __MESH_H__
