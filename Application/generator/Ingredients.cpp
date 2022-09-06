//
// Created by milosvasic on 29.08.22.
//

#include "Ingredients.h"

#include <utility>

#include "algorithm"

Ingredients::Ingredients(std::string description) {

    this->description = std::move(description);
}

std::string Ingredients::getDescription() {

    return this->description;
}

std::vector<std::shared_ptr<ClassPropertyIngredient>> *Ingredients::getProperties() {

    return &this->properties;
}

bool Ingredients::addProperty(ClassPropertyIngredient &property) {

    size_t size = this->properties.size();
    auto ptr = std::make_shared<ClassPropertyIngredient>(property);
    this->properties.push_back(ptr);
    return size != this->properties.size();
}

void Ingredients::setClassName(ClassNameIngredient *name) {

    this->className = name;
}

ClassNameIngredient *Ingredients::getClassName() {

    return this->className;
}