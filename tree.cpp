#include "tree.h"

AVLTree::AVLTree() : root(nullptr) {
    name[0] = '\0';
}

AVLTree::~AVLTree() {
    destroy();
}

void AVLTree::setName(const char* n) {
    std::strncpy(name, n, 19);
    name[19] = '\0';
}

const char* AVLTree::getName() const {
    return name;
}

void AVLTree::create() {
    destroy();
}

void AVLTree::destroy() {
    freeTree(root);
    root = nullptr;
}

void AVLTree::freeTree(TNode* node) {
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

int AVLTree::getHeight(TNode* node) const {
    return (node == nullptr) ? 0 : node->height;
}

int AVLTree::getBalance(TNode* node) const {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

TNode* AVLTree::rightRotate(TNode* y) {
    TNode* x = y->left;
    TNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

TNode* AVLTree::leftRotate(TNode* x) {
    TNode* y = x->right;
    TNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

TNode* AVLTree::insertNode(TNode* node, int key) {
    if (node == nullptr) {
        return new TNode(key);
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    // Right Right
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(int key) {
    root = insertNode(root, key);
}

TNode* AVLTree::minValueNode(TNode* node) const {
    TNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

TNode* AVLTree::removeNode(TNode* node, int key, bool& removed) {
    if (node == nullptr) return node;

    if (key < node->key) {
        node->left = removeNode(node->left, key, removed);
    } else if (key > node->key) {
        node->right = removeNode(node->right, key, removed);
    } else {
        removed = true;
        if ((node->left == nullptr) || (node->right == nullptr)) {
            TNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            TNode* temp = minValueNode(node->right);
            node->key = temp->key;
            bool dummy = false;
            node->right = removeNode(node->right, temp->key, dummy);
        }
    }

    if (node == nullptr) return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }
    // Left Right
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Right
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }
    // Right Left
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

bool AVLTree::remove(int key) {
    bool removed = false;
    root = removeNode(root, key, removed);
    return removed;
}

TNode* AVLTree::searchNode(TNode* node, int key) const {
    if (node == nullptr || node->key == key) return node;
    if (key < node->key) return searchNode(node->left, key);
    return searchNode(node->right, key);
}

bool AVLTree::search(int key) const {
    return searchNode(root, key) != nullptr;
}

TNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::countNodes(TNode* node, int& count) const {
    if (node == nullptr) return;
    count++;
    countNodes(node->left, count);
    countNodes(node->right, count);
}

int AVLTree::getCount() const {
    int count = 0;
    countNodes(root, count);
    return count;
}

void AVLTree::printHorizontal(TNode* node, int level) const {
    if (node == nullptr) return;
    printHorizontal(node->right, level + 1);
    for (int i = 0; i < level; i++) std::cout << "    ";
    std::cout << node->key << " (h:" << node->height << ")\n";
    printHorizontal(node->left, level + 1);
}

void AVLTree::print() const {
    if (root == nullptr) {
        std::cout << "Дерево " << name << " пустое\n";
        return;
    }
    std::cout << "АВЛ-дерево " << name << ":\n";
    printHorizontal(root, 0);
}

void AVLTree::saveNodes(TNode* node, std::ofstream& file) const {
    if (node == nullptr) return;
    file << node->key << " ";
    saveNodes(node->left, file);
    saveNodes(node->right, file);
}

void AVLTree::save(std::ofstream& file) const {
    int count = getCount();
    file << name << " " << count << " ";
    saveNodes(root, file);
    file << "\n";
}

void AVLTree::load(std::ifstream& file) {
    destroy();
    int count = 0;
    if (!(file >> name >> count)) return;
    for (int i = 0; i < count; ++i) {
        int val;
        if (file >> val) {
            insert(val);
        }
    }
}
