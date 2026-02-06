#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/CCFileUtils.hpp>

using namespace geode::prelude;

class $modify(MyFileUtils, CCFileUtils) {
    gd::string fullPathForFilename(const char* filename, bool resourceDirectory) {
        auto path = CCFileUtils::fullPathForFilename(filename, resourceDirectory);
        if (path.empty() && std::string(filename).find("-uhd") != std::string::npos) {
            std::string fallback = filename;
            size_t pos = fallback.find("-uhd");
            if (pos != std::string::npos) {
                fallback.replace(pos, 4, "-hd");
                return CCFileUtils::fullPathForFilename(fallback.c_str(), resourceDirectory);
            }
        }
        return path;
    }
};

class $modify(MyGameManager, GameManager) {
    bool canUseHighGraphics() { 
        return true; 
    }
};
