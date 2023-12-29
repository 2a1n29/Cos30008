#include "Polygon.h"

float Polygon::getSignedArea() const
{
    float Result = 0.0f;

    if (fNumberOfVertices > 2)
    {
        for (size_t i = 0; i < fNumberOfVertices; i++)
        {
            size_t j = (i + 1) % fNumberOfVertices;
            Result = 1.0 / 2.0 * ((fVertices[i].getX() * fVertices[j].getY()) - (fVertices[j].getX() * fVertices[i].getY())) + Result;
        }
    }   
    return (Result);
}