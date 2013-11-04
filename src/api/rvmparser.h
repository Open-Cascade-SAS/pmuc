#ifndef RVMPARSER_H
#define RVMPARSER_H

#include <istream>
#include <string>
#include <vector>

#include "vector3f.h"

class RVMReader;

/**
 * @brief The RVMParser class
 * This is a parser class able to read RVM data from either:
 *   - a file,
 *   - a character buffer,
 *   - or a standard input stream.
 *
 * In the case of a file, a .att companion file will be searched int he same directory to include metadata.
 *
 * Two methods are provided to allow tweeking the output:
 * @see setObjectName @see setForcedColor
 */
class RVMParser
{
    public:
        /**
         * @brief Constructs a parser ready to send data to the provided RVMReader
         * @param reader The reader object that will receive the data.
         */
        RVMParser(RVMReader* reader);

        /**
         * @brief Reads from a file a parse its content.
         * @param filename the file name
         * @param ignoreAttributes if set to true, allows to ignore the .att companion file
         * @return true if the parsing was a success.
         */
        bool readFile(const std::string& filename, bool ignoreAttributes);
        /**
         * @brief Reads from a character buffer.
         * @param buffer the character buffer containing RVM data.
         * @return true if the parsing was a success.
         */
        bool readBuffer(const char* buffer);
        /**
         * @brief Reads RVM data from an input stream
         * @param is the input stream of RVM data.
         * @return true if the parsing was a success.
         */
        bool readStream(std::istream& is);

        /**
         * @brief Allow to filter the RVM data to one named object
         * @param name the name of the object to extract.
         */
        void setObjectName(const std::string& name) { m_objectName = name; }
        /**
         * @brief Force the color of all extracted objects
         * @param index a PDMS color index
         */
        void setForcedColor(const int index) { m_forcedColor = index; }

        /**
         * @brief In case of error, returns the last error that occured.
         * @return a string describing the error.
         */
        const std::string lastError();

        /**
         * @brief Statistics of the parsing: number of groups
         * @return the number of groups found in the source.
         */
        const int& nbGroups() { return m_nbGroups; }
        /**
         * @brief Statistics of the parsing: number of pyramids
         * @return the number of pyramids found in the source.
         */
        const int& nbPyramids() { return m_nbPyramids; }
        /**
         * @brief Statistics of the parsing: number of boxes
         * @return the number of boxes found in the source.
         */
        const int& nbBoxes() { return m_nbBoxes; }
        /**
         * @brief Statistics of the parsing: number of rectangular toruses
         * @return the number of rectangular toruses found in the source.
         */
        const int& nbRectangularToruses() { return m_nbRectangularToruses; }
        /**
         * @brief Statistics of the parsing: number of circular toruses
         * @return the number of circular toruses found in the source.
         */
        const int& nbCircularToruses() { return m_nbCircularToruses; }
        /**
         * @brief Statistics of the parsing: number of elliptical dishes
         * @return the number of elliptical dishes found in the source.
         */
        const int& nbEllipticalDishes() { return m_nbEllipticalDishes; }
        /**
         * @brief Statistics of the parsing: number of spherical dishes
         * @return the number of spherical dishes found in the source.
         */
        const int& nbSphericalDishes() { return m_nbSphericalDishes; }
        /**
         * @brief Statistics of the parsing: number of snouts
         * @return the number of snouts found in the source.
         */
        const int& nbSnouts() { return m_nbSnouts; }
        /**
         * @brief Statistics of the parsing: number of cylinders
         * @return the number of cylinders found in the source.
         */
        const int& nbCylinders() { return m_nbCylinders; }
        /**
         * @brief Statistics of the parsing: number of spheres
         * @return the number of spheres found in the source.
         */
        const int& nbSpheres() { return m_nbSpheres; }
        /**
         * @brief Statistics of the parsing: number of lines
         * @return the number of lines found in the source.
         */
        const int& nbLines() { return m_nbLines; }
        /**
         * @brief Statistics of the parsing: number of facet groups
         * @return the number of facet groups found in the source.
         */
        const int& nbFacetGroups() { return m_nbFacetGroups; }
        /**
         * @brief Statistics of the parsing: number of attributes
         * @return the number of attributes found in the source.
         */
        const long& nbAttributes() { return m_attributes; }

    private:
        bool readGroup(std::istream& is);
        bool readPrimitive(std::istream& is);

        std::string readIdentifier(std::istream& is);
        std::string readString(std::istream& is);
        std::vector<float> readMatrix(std::istream& is);
        std::vector<float> readBoundingBox(std::istream& is);
        std::vector<float> readVector(std::istream& is);
        std::vector<std::vector<std::vector<std::pair<Vector3F, Vector3F> > > > readFacetGroup(std::istream& is);
        unsigned int readInt(std::istream& is);
        float readFloat(std::istream &is);
        char readChar(std::istream& is);

        RVMReader* m_reader;
        std::string m_lastError;

        std::istream*   m_attributeStream;
        std::string     m_currentAttributeLine;
        const char*     m_buffer;
        bool            m_headerFound;
        std::string     m_objectName;
        int             m_objectFound;
        int             m_forcedColor;

        int             m_nbGroups;
        int             m_nbPyramids;
        int             m_nbBoxes;
        int             m_nbRectangularToruses;
        int             m_nbCircularToruses;
        int             m_nbEllipticalDishes;
        int             m_nbSphericalDishes;
        int             m_nbSnouts;
        int             m_nbCylinders;
        int             m_nbSpheres;
        int             m_nbLines;
        int             m_nbFacetGroups;
        long            m_attributes;
};

#endif // RVMPARSER_H