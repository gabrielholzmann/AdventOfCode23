#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

std::vector<int> readNumbers(FILE *fp) {
    std::vector<int> numbers;

    char line[100];
    fgets(line, 100, fp);

    char *num = line;

    while (num) {
        num++;
        if (isdigit(*num)) {
            numbers.push_back(atoi(num));
            num = strchr(num, ' ');
        }
    }


    return numbers;
}

int waysOfWinning(int time, int distance) {
    int totalWaysOfWinning = 0;

    for (int hold = 0; hold <= time; hold++) {
        int remainingTime = time - hold;
        int distanceTravelled = hold * remainingTime;

        if (distanceTravelled > distance) {
            totalWaysOfWinning++;
        }
    }


    return totalWaysOfWinning;
}

int waysOfWinningQuadratic(int time, int distance) {
    //h * (t - h) > d
    //-h^2 + th > d
    //-h^2 + th - d > 0
    //h^2 - th + d < 0

    int a = 1;
    int b = -time;
    int c = distance;

    float discriminant1 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    float discriminant2 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

    discriminant1 = std::floor(discriminant1);
    discriminant2 = std::ceil(discriminant2);


    return (int)(discriminant2 - discriminant1 - 1);
}

int main() {
    FILE *fp = fopen("../input.txt", "r");
    if (!fp) {
        std::cerr << "File not found" << std::endl;
        return 1;
    }

    std::vector<int> time = readNumbers(fp);
    std::vector<int> distance = readNumbers(fp);

    int bruteForce = 1;
    int quadratic = 1;

    for (int i = 0; i < time.size(); i++) {
        quadratic *= waysOfWinningQuadratic(time[i], distance[i]);
        bruteForce *= waysOfWinning(time[i], distance[i]);
    }

    std::cout << "Quadratic: " << quadratic << std::endl;
    std::cout << "Brute Force: " << bruteForce << std::endl;

    fclose(fp);

    return 0;
}
