#include "WindowsLeaderboardManager.h"

#include "platform/leaderboards/LeaderboardManager.h"

LeaderboardManager* LeaderboardManager::m_instance =
    new WindowsLeaderboardManager(); // Singleton instance of the
                                     // LeaderboardManager
