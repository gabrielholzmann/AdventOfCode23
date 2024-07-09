#include <iostream>
#include <unordered_map>
#include <cstring>

typedef struct node {
    node *right{};
    node *left{};
} node;

node *getNode(std::unordered_map<std::string, node *> &nodes, const std::string &name) {
    if (!nodes.count(name)) {
        node *n = new node();
        nodes[name] = n;
        return n;
    } else {
        return nodes[name];
    }
}

std::unordered_map<std::string, node *> readNodes(FILE *fp) {
    std::unordered_map<std::string, node *> nodes;

    //advance to the next line
    char line[20];
    fgets(line, 20, fp);

    while (fgets(line, 20, fp)) {
        char nodeChar[4];
        char left[4];
        char right[4];

        sscanf(line, "%3s = (%3s, %3s)", nodeChar, left, right);

        node *n = getNode(nodes, nodeChar);
        n->left = getNode(nodes, left);
        n->right = getNode(nodes, right);

    }

    return nodes;
}

int findPath(node *start, node *end, char instructions []) {
    //-1 to account for \n
    int instructionsLength = strlen(instructions) - 1;
    int instructionIndex = 0;
    int totalSteps = 0;

    while (start != end) {
        char i = instructions[instructionIndex];

        if (i == 'L')
            start = start->left;
        else
            start = start->right;

        instructionIndex = (instructionIndex + 1) % instructionsLength;
        totalSteps++;
    }
    return totalSteps;
}

int main() {
    FILE *fp = fopen("../input.txt", "r");
    if (!fp) {
        std::cerr << "Error: cannot open file" << std::endl;
        return 1;
    }

    char instructions[300];
    fgets(instructions, 300, fp);

    std::unordered_map<std::string, node *> nodes = readNodes(fp);

    int r = findPath(nodes["AAA"], nodes["ZZZ"], instructions);
    std::cout << r;

    fclose(fp);

    return 0;
}
