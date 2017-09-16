//
// Created by xbili on 9/16/17.
//

#include <string>
#include "DataReader.h"
#include "../lib/csv.h"

using std::string;

DataReader::DataReader(string fileName, int numColumns , int labelColumn, int numRows) {
    m_fileName = fileName;
    m_numColumns = numColumns;
    m_labelColumn = labelColumn;

    // Allocate space for inputs
    m_inputs = new float*[numRows];
    for (int i = 0; i < numRows; i++) {
        m_inputs[i] = new float[numColumns - 1];
    }

    // Allocate space for labels
    m_labels = new float[numRows];

    // Read from CSV
    io::LineReader* reader = new io::LineReader(m_fileName);
    int rowNum = 0;
    while (char* line = reader->next_line()) {
        std::vector<char*> row;
        row.push_back(line);
        while (*line != '\0') {
            if (*line == ',') {
                *line = '\0';
                row.push_back(line+1);
            }
            line++;
        }

        m_labels[rowNum] = strtof(row.at(0), NULL);
        for (int i = 1; i < row.size(); i++) {
            m_inputs[rowNum][i-1] = strtof(row.at(i), NULL);
        }

        rowNum++;
    }
}

DataReader::~DataReader() {}

float **DataReader::getInputs() const {
    return m_inputs;
}

float *DataReader::getLabels() const {
    return m_labels;
}
