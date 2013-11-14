#include "EncodeUtilities.hpp"

#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

EncodeUtilities::EncodeUtilities(std::vector<size_t> const &frequencies)
    : frequencies_(std::vector<size_t>(frequencies)), dictionarySize_(frequencies_.size())
{
    std::priority_queue<Node *, std::vector<Node *>, NodeComparer> queue;

    for (int i = 0; i < (int)frequencies_.size(); ++i) {
        if (frequencies_[i])
            queue.push(new Node(frequencies_[i], i));
    }

    // anti single-character-file bugfix: adding dummy nodes
    if (queue.size() == 0) {
        queue.push(new Node(0, 0));
        queue.push(new Node(0, 1));
    }
    if (queue.size() == 1) {
        if (queue.top()->symbol_ == 0)
            queue.push(new Node(0, 1));
        else
            queue.push(new Node(0, 0));
    }

    while (queue.size() > 1) {
        Node *childR = queue.top();
        queue.pop();
        Node *childL = queue.top();
        queue.pop();
        Node *parent = new Node(childL, childR);
        queue.push(parent);
    }

    codeLengths_.assign(dictionarySize_, 0);
    walk(queue.top());
    delete queue.top();

    int maxCodeLength = *max_element(codeLengths_.begin(), codeLengths_.end());
    if (numberInternals_.size() < size_t(maxCodeLength + 1))
        numberInternals_.resize(maxCodeLength + 1, 0);
    ComputeCodes(maxCodeLength);
    ComputeSortedSymbols();
    ComputeOffset(maxCodeLength);
}

void EncodeUtilities::walk(Node *currentNode, int currentDeep)
{
    if (currentNode) {
        walk(currentNode->left_, currentDeep + 1);
        if (currentNode->symbol_ != -1)
            codeLengths_[currentNode->symbol_] = currentDeep;
        if (currentNode->symbol_ == -1) {
            if (numberInternals_.size() < size_t(currentDeep + 1))
                numberInternals_.resize(currentDeep + 1, 0);
            numberInternals_[currentDeep]++;
        }

        walk(currentNode->right_, currentDeep + 1);
    }
}

void EncodeUtilities::ComputeCodes(int maxCodeLength)
{
    std::vector<int> numberLeafs(maxCodeLength + 1, 0);
    for (size_t i = 0; i < dictionarySize_; ++i) {
        if (codeLengths_[i])
            numberLeafs[codeLengths_[i]]++;
    }

    std::vector<int> S(maxCodeLength + 1, 0);
    for (int i = maxCodeLength - 1; i > 0; --i) {
        S[i] = (S[i + 1] + numberLeafs[i + 1]) >> 1;
    }

    codes_.assign(dictionarySize_, -1);
    for (size_t i = 0; i < dictionarySize_; ++i) {
        if (codeLengths_[i]) {
            codes_[i] = S[codeLengths_[i]];
            S[codeLengths_[i]]++;
        }
    }
}

void EncodeUtilities::ComputeSortedSymbols()
{
    sortedSymbols_.clear();
    for (size_t i = 0; i < dictionarySize_; ++i) {
        if (codeLengths_[i])
            sortedSymbols_.push_back(std::make_pair(i, codeLengths_[i]));
    }
    sort(sortedSymbols_.begin(), sortedSymbols_.end(), compareCodes);
}

void EncodeUtilities::ComputeOffset(int maxCodeLength)
{
    offset_.assign(maxCodeLength + 1, -1);
    for (int i = 0; i < (int)sortedSymbols_.size(); ++i) {
        int len = sortedSymbols_[i].second;
        if (offset_[len] == -1)
            offset_[len] = i;
    }
}

bool EncodeUtilities::compareCodes(std::pair<int, int> x, std::pair<int, int> y)
{
    if (x.second != y.second)
        return x.second > y.second;
    else
        return x.first < y.first;
}
