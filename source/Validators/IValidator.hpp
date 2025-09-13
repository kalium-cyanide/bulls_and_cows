#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

struct IValidator
{
    virtual bool operator() (std::string value) = 0;
};
