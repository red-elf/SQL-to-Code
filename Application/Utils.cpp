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

ClassPropertyDataType Utils::dataTypeToClassPropertyDataType(DataType &dataType) {

    switch (dataType) {
        case DataType::BOOLEAN:
            return ClassPropertyDataType::BOOLEAN;
        case DataType::CHAR:
            return ClassPropertyDataType::CHAR;
        case DataType::DATE:
        case DataType::TIME:
        case DataType::DATETIME:
        case DataType::BIGINT:
        case DataType::LONG:
            return ClassPropertyDataType::LONG;
        case DataType::FLOAT:
            return ClassPropertyDataType::FLOAT;
        case DataType::DOUBLE:
        case DataType::REAL:
        case DataType::DECIMAL:
            return ClassPropertyDataType::DOUBLE;
        case DataType::INT:
        case DataType::SMALLINT:
            return ClassPropertyDataType::INT;
        case DataType::TEXT:
        case DataType::VARCHAR:
            return ClassPropertyDataType::STRING;
        default:
            throw std::invalid_argument("Unable to determine the data type");
    }
}
