//
// Created by xbili on 9/16/17.
//

#include <string>
#include <vector>
#include "DataReader.h"
#include "../lib/csv.h"

using namespace std;

DataReader::DataReader(string fileName) {
    m_fileName = fileName;

    // Read from CSV
    io::LineReader* reader = new io::LineReader(m_fileName);
    int rowNum = 0;
    while (char* line = reader->next_line()) {
        vector<float> inputs;
        vector<char*> row;

        row.push_back(line);

        while (*line != '\0') {
            if (*line == ',') {
                *line = '\0';
                row.push_back(line+1);
            }
            line++;
        }

        m_labels.push_back(strtof(row.at(0), NULL));

        for (int i = 1; i < row.size(); i++) {
            inputs.push_back(strtof(row.at(i), NULL));
        }
        m_inputs.push_back(inputs);

        rowNum++;
    }
}

DataReader::~DataReader() {}

vector<vector<float>> DataReader::getInputs() const {
    return m_inputs;
}

vector<float> DataReader::getLabels() const {
    return m_labels;
}
