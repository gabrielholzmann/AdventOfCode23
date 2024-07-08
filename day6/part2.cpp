#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

long readNumber(FILE *fp) {
    long number = 0;

    char line[100];
    fgets(line, 100, fp);

    char *num = line;

    while (*num != '\0') {
        if (isdigit(*num)) {
            number *= 10;
            number += *num - '0';
        }
        num++;
    }

    return number;
}

long waysOfWinning(long time, long distance) {
    int totalWaysOfWinning = 0;

    for (int hold = 0; hold <= time; hold++) {
        long remainingTime = time - hold;
        long distanceTravelled = hold * remainingTime;

        if (distanceTravelled > distance) {
            totalWaysOfWinning++;
        }
    }


    return totalWaysOfWinning;
}

long waysOfWinningQuadratic(long time, long distance) {
    //h * (t - h) > d
    //-h^2 + th > d
    //-h^2 + th - d > 0
    //h^2 - th + d < 0

    long a = 1;
    long b = -time;
    long c = distance;

    double discriminant1 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    double discriminant2 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

    discriminant1 = std::floor(discriminant1);
    discriminant2 = std::ceil(discriminant2);


    return (long)(discriminant2 - discriminant1 - 1);
}

int main() {
    FILE *fp = fopen("../input.txt", "r");
    if (!fp) {
        std::cerr << "File not found" << std::endl;
        return 1;
    }

    long time = readNumber(fp);
    long distance = readNumber(fp);

    long quadratic = waysOfWinningQuadratic(time, distance);
    long bruteForce = waysOfWinning(time, distance);

    std::cout << "Quadratic: " << quadratic << std::endl;
    std::cout << "Brute Force: " << bruteForce << std::endl;


    fclose(fp);

    return 0;
}
