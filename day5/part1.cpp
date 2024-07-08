#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

typedef struct seedMapping {
    long destinationStart;
    long sourceStart;
    long rangeLength;
} seedMapping;

std::vector<long> readSeeds(FILE *fp) {
    std::vector<long> seeds;

    char line[250];
    fgets(line, 250, fp);

    char *seedChar = line + 6;

    while(seedChar) {
        seeds.emplace_back(atol(++seedChar));
        seedChar = strchr(seedChar, ' ');
    }

    return seeds;
}

std::vector<std::vector<seedMapping>> readMappings(FILE *fp) {
    char line[100];

    std::vector<std::vector<seedMapping>> mappings(7);
    int mappingIndex = -1;

    while (fgets(line, 100, fp)) {
        if (line[0] == '\n')
            mappingIndex++;
        else if (isdigit(line[0])) {
            seedMapping map;

            sscanf(line, "%ld %ld %ld", &map.destinationStart, &map.sourceStart, &map.rangeLength);

            mappings[mappingIndex].emplace_back(map);
        }
    }

    return mappings;
}

long calculateMappings(long seed, std::vector<std::vector<seedMapping>> &mappings) {
    for (auto const &map : mappings) {
        for (auto const &detail : map) {
            if (seed >= detail.sourceStart && seed <= detail.sourceStart + detail.rangeLength) {
                long offset = seed - detail.sourceStart;
                seed = detail.destinationStart + offset;
                break;
            }
        }
    }

    return seed;
}

int main() {
    FILE *fp = fopen("../input.txt", "r");
    if (!fp) {
        std::cout << "Error opening file\n";
        return -1;
    }

    auto seeds = readSeeds(fp);
    auto mappings = readMappings(fp);

    long lowest = LONG_MAX;
    for (auto &s : seeds) {
        s = calculateMappings(s, mappings);

        if (s < lowest)
            lowest = s;
    }

    std::cout << lowest;

    fclose(fp);

    return 0;
}
