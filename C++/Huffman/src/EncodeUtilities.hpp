#ifndef ENCODEUTILITIES_HPP
#define ENCODEUTILITIES_HPP

#include <vector>
#include <cstddef>

class EncodeUtilities {
public:
    explicit EncodeUtilities(std::vector<size_t> const &frequencies);

    std::vector<size_t> const &GetFrequencies() const
    {
        return frequencies_;
    }

    std::vector<int> const &GetCodeLengths() const
    {
        return codeLengths_;
    }

    std::vector<int> const &GetNumberInternals() const
    {
        return numberInternals_;
    }

    std::vector<int> const &GetCodes() const
    {
        return codes_;
    }

    std::vector<std::pair<int, int> > const &GetSortedSymbols() const
    {
        return sortedSymbols_;
    }

    std::vector<int> const &GetOffset() const
    {
        return offset_;
    }

private:
    struct Node {
        Node();
        Node(size_t frequency, int symbol = -1, Node *left = NULL, Node *right = NULL)
            : frequency_(frequency), symbol_(symbol), left_(left), right_(right)
        {
        }
        Node(Node *left, Node *right, int symbol = -1)
            : frequency_(left->frequency_ + right->frequency_),
              symbol_(symbol),
              left_(left),
              right_(right)
        {
        }

        ~Node()
        {
            delete left_;
            delete right_;
        }

        size_t frequency_;
        int symbol_;
        Node *left_;
        Node *right_;
    };

    struct NodeComparer {
        bool operator()(Node const *left, Node const *right) const
        {
            return left->frequency_ > right->frequency_;
        }
    };

    void walk(Node *currentNode, int currentDeep = 0);

    static bool compareCodes(std::pair<int, int> x, std::pair<int, int> y);

    void ComputeCodes(int maxCodeLength);
    void ComputeSortedSymbols();
    void ComputeOffset(int maxCodeLength);

    std::vector<size_t> frequencies_;
    std::vector<int> codeLengths_;
    std::vector<int> numberInternals_;

    std::vector<int> codes_;
    std::vector<std::pair<int, int> > sortedSymbols_;
    std::vector<int> offset_;

    size_t dictionarySize_;
};

#endif /* end of include guard: ENCODEUTILITIES_HPP */
