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

long calculateMappings(std::pair<long, long> seed, std::vector<std::vector<seedMapping>> &mappings) {
    std::vector<std::pair<long, long>> toBeMapped;
    std::vector<std::pair<long, long>> alreadyMapped;
    toBeMapped.emplace_back(seed);

    for (auto const &map : mappings) {
        while (!toBeMapped.empty()) {
            std::pair<long, long> r = toBeMapped.back();
            toBeMapped.pop_back();

            bool isMapped = false;
            for (auto const &detail: map) {
                long overlapStart = std::max(r.first, detail.sourceStart);
                long overlapEnd = std::min(r.second, detail.sourceStart + detail.rangeLength);

                if (overlapStart < overlapEnd) {
                    alreadyMapped.emplace_back(overlapStart - detail.sourceStart + detail.destinationStart, overlapEnd - detail.sourceStart + detail.destinationStart);
                    isMapped = true;

                    if (overlapStart > r.first) {
                        toBeMapped.emplace_back(r.first, overlapStart);
                    }
                    if (overlapEnd < r.second) {
                        toBeMapped.emplace_back(overlapEnd, r.second);
                    }
                    break;
                }
            }
            //didn't overlap
            if (!isMapped)
                alreadyMapped.emplace_back(r);
        }
        toBeMapped = alreadyMapped;
        alreadyMapped.clear();
    }

    long lowest = LONG_MAX;
    for (auto &s : toBeMapped) {
        if (s.first < lowest)
            lowest = s.first;
    }

    return lowest;
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
    for (int i = 0; i < seeds.size(); i += 2) {
        std::pair<long, long> range = {seeds[i], seeds[i] + seeds[i + 1] - 1};

        long result = calculateMappings(range, mappings);
        if (result < lowest)
            lowest = result;
    }

    std::cout << lowest;

    fclose(fp);

    return 0;
}
