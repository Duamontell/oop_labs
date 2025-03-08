#pragma once

#include <iostream>
#include <string>

std::string HtmlDecode(const std::string& html);
std::string DecodeEntity(const std::string& entity, bool& found);
