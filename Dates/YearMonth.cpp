#include <emscripten.h>
#include <cstdint>
#include <time.h>
#include <vector>

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    uint32_t *getStartOfMonthArray(int32_t *timestamps, int timestampNum)
    {
        static int koeff = 400;
        uint32_t values[100001];

        std::vector<uint32_t> startOfMonthTimestamps;
        startOfMonthTimestamps.reserve(timestampNum > 1000 ? timestampNum / 400 : timestampNum);

        bool reverse = timestamps[0] > timestamps[timestampNum - 1];

        int idx = 1;
        for (
            int i = reverse ? timestampNum - 1 : 0;
            (reverse && i >= 0) || (!reverse && i < timestampNum);
            reverse ? i-- : i++
        )
        {
            time_t timestamp = (const time_t)timestamps[i];
            struct tm *aTime = localtime(&timestamp);

            aTime->tm_mday = 1;
            aTime->tm_wday = 0;
            aTime->tm_hour = 0;
            aTime->tm_min = 0;
            aTime->tm_sec = 0;

            time_t startOfMonth = mktime(aTime);

            // Avoid duplicates
            if (idx == 1 || values[idx - 1] != startOfMonth) {
                values[idx] = startOfMonth;
                idx++;
            }
        }

        values[0] = idx - 1;

        auto arrayPtr = &values[0];
        return arrayPtr;
    }
}
