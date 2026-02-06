#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/CCFileUtils.hpp>

using namespace geode::prelude;

// Evita fallos si el juego busca texturas que no existen
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
    // Habilita los botones de High Graphics siempre
    bool canUseHighGraphics() { return true; }

    void updateQuality(int quality) {
        GameManager::updateQuality(quality);
        auto conf = CCFileUtils::sharedFileUtils();
        conf->purgeCachedEntries();
        log::info("Calidad de texturas forzada a: {}", quality);
    }
};
