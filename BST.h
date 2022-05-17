#ifndef BST_H
#define BST_H

#include <iostream>

using std::cout;
using std::endl;

template<class T>
struct Node
{
    Node(const T& dat): data(dat), lLink(nullptr), rLink(nullptr){}

    /// The actual data to be stored into the Binary Search Tree
    T data;

    /// The left link connecting a node
    Node<T>* lLink;

    /// The right link connecting a node
    Node<T>* rLink;
};

template <class T>
class BST
{
public:

    /**
     * @brief Constructor for the BST class
     */
    BST();

    /**
     * @brief Destructor for the BST class
     */
    ~BST();

    /**
     * @brief Copy constructor for the BST class
     *
     * @param newBST - reference to a constant BST object
     */
    BST(const BST<T>& newBST);

    /**
     * @brief Assignment operator for the BST class
     *
     * @param newBST - a constant BST reference
     *
     * @return BST<T>& - a reference to a BST object containing T elements
     */
    BST<T>& operator=(const BST<T>& newBST);

    /**
     * @brief insert an element into the BST
     *
     * @param item - reference to a constant generic type
     *
     * @return void
     */
    void Insert(const T& item);

    /**
     * @brief search for an element in the BST
     *
     * @param item - reference to a constant generic type
     *
     * @return void
     */
    bool Search(const T& item);

    /**
     * @brief traverse the nodes of the BST in-order
     *
     * @return void
     */
    void InOrder() const;

    /**
     * @brief traverse the nodes of the BST in pre-order
     *
     * @return void
     */
    void PreOrder() const;

    /**
     * @brief display the elements of the BST in post-order
     *
     * @return void
     */
    void PostOrder() const;
private:
    /// The root node of the BST
    Node<T>* m_root;

    /**
     * @brief Copy a node into another node
     *
     * @param item - reference to a constant generic type
     *
     * @param prevNode - The original node to be copied
     *
     * @param newNode - The new node that will contain the previous node
     *
     * @return void
     */
    void Copy(Node<T>* &prevNode, Node<T>* newNode);

    /**
     * @brief insert an element into the BST
     *
     * @param parentNode -
     *
     * @param newNode -
     *
     * @return void
     */
    void insert(Node<T>* parentNode, Node<T>* newNode);

    /**
     * @brief search for an element in the BST. Returns true if element is found
     *
     * @param currentNode - a constant reference to the current node containing an element
     *
     * @param item - reference to a constant generic type
     *
     * @return bool
     */
    bool search(const Node<T>* currentNode, const T& item) const;

    /**
     * @brief traverse through the nodes of the BST in-order
     *
     * @param currentNode - the current node when being traversed down the tree
     *
     * @return void
     */
    void inOrder(const Node<T>* currentNode) const;

    /**
     * @brief traverse through the nodes of the BST in pre-order
     *
     * @param currentNode - the current node when being traversed down the tree
     *
     * @return void
     */
    void preOrder(const Node<T>* currentNode) const;

    /**
     * @brief traverse through the nodes of the BST in post-order
     *
     * @param currentNode - the current node when being traversed down the tree
     *
     * @return void
     */
    void postOrder(const Node<T>* currentNode) const;

    /**
     * @brief Deallocate memory for each node of the tree, starting from the root node
     *
     * @param root - A reference to the address of the root of the BST to be removed
     *
     * @return void
     */
    void Destroy(Node<T>* &root);
};

template<class T>
BST<T>::BST()
{
    m_root = nullptr;
}

template<class T>
BST<T>::~BST()
{
    Destroy(m_root);
}

template<class T>
BST<T>::BST(const BST<T>& newBST)
{
    if (newBST.m_root == nullptr)
        m_root = nullptr;
    else
        Copy(m_root, newBST.m_root);
}

template<class T>
void BST<T>::Copy(Node<T>* &prevNode, Node<T>* newNode)
{
    if (prevNode == nullptr)
        newNode = nullptr;
    else
    {
        newNode = new Node<T>(prevNode->data);
        Copy(prevNode->lLink, newNode->lLink);
        Copy(prevNode->rLink, newNode->rLink);
    }
}

template<class T>
BST<T>& BST<T>::operator=(const BST<T>& newBST)
{
    // Avoid self assignment
    if (this != &newBST)
    {
        if (m_root != nullptr)
            Destroy(m_root);

        if (newBST.m_root == nullptr)
            m_root = nullptr;
        else
            Copy(m_root, newBST.m_root);
    }

    return *this;
}

template<class T>
void BST<T>::Insert(const T& item)
{
    Node<T>* newNode = new Node<T>(item);

    if (m_root == nullptr)
        m_root = newNode;
    else
        insert(m_root, newNode);
}

template<class T>
void BST<T>::insert(Node<T>* parentNode, Node<T>* newNode)
{
    if (newNode->data < parentNode->data)
    {
        if (parentNode->lLink == nullptr)
            parentNode->lLink = newNode;
        else
            insert(parentNode->lLink, newNode);
    }
    else
    {
        if (newNode->data == parentNode->data)
            return;

        if (parentNode->rLink == nullptr)
            parentNode->rLink = newNode;
        else
            insert(parentNode->rLink, newNode);
    }
}

template<class T>
bool BST<T>::Search(const T& item)
{
    return search(m_root, item);
}

template<class T>
bool BST<T>::search(const Node<T>* currentNode, const T& item) const
{
    if (currentNode == nullptr)
        return false;
    else
    {
        if (currentNode->data == item)
            return true;
        else if (currentNode->data > item)
            search(currentNode->lLink, item);
        else
            search(currentNode->rLink, item);
    }
}

template<class T>
void BST<T>::InOrder() const
{
    inOrder(m_root);
}

template<class T>
void BST<T>::inOrder(const Node<T>* currentNode) const
{
    if (currentNode != nullptr)
    {
        inOrder(currentNode->lLink);
        cout << currentNode->data << '\n';
        inOrder(currentNode->rLink);
    }
}

template<class T>
void BST<T>::PreOrder() const
{
    preOrder(m_root);
}

template<class T>
void BST<T>::preOrder(const Node<T>* currentNode) const
{
    if (currentNode != nullptr)
    {
        cout << currentNode->data << '\n';
        preOrder(currentNode->lLink);
        preOrder(currentNode->rLink);
    }
}

template<class T>
void BST<T>::PostOrder() const
{
    postOrder(m_root);
}

template<class T>
void BST<T>::postOrder(const Node<T>* currentNode) const
{
    if (currentNode != nullptr)
    {
        postOrder(currentNode->lLink);
        postOrder(currentNode->rLink);
        cout << currentNode->data << '\n';
    }
}

template<class T>
void BST<T>::Destroy(Node<T>* &root)
{
    // No point deleting something that doesn't exist
    if (root != nullptr)
    {
        Destroy(root->lLink);
        Destroy(root->rLink);
        delete root;
        root = nullptr;
    }
}

#endif // BST_H
