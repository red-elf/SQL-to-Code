//
// Created by milosvasic on 13.08.22.
//
#include "Utils.h"

std::string Utils::dataTypeToString(DataType &dataType) {

    switch (dataType) {
        case DataType::BOOLEAN:
            return "Boolean";
        case DataType::CHAR:
            return "Char";
        case DataType::DATE:
        case DataType::TIME:
        case DataType::DATETIME:
        case DataType::BIGINT:
        case DataType::LONG:
            return "Long";
        case DataType::FLOAT:
            return "Float";
        case DataType::DOUBLE:
        case DataType::REAL:
        case DataType::DECIMAL:
            return "Double";
        case DataType::INT:
        case DataType::SMALLINT:
            return "Integer";
        case DataType::TEXT:
        case DataType::VARCHAR:
            return "String";
        default:
            throw std::invalid_argument("Unable to determine the data type");
    }
}
