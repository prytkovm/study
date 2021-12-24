#include <cstdlib>
#include <ctime>
#include <string>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>

struct coordinates
{
    double x, y;
    char key;
};

struct AVL_tree_node
{
    int value;
    unsigned height;
    coordinates coordinates;
    AVL_tree_node *left, *right;
    AVL_tree_node(int val, char key) {this->value = val; left = right = nullptr; height = 1; this->coordinates.key = key;}
};

struct tree_node
{
    int value;
    tree_node *left, *right;
    coordinates coordinates;
    tree_node(int val, char key) {this->value = val; left= right = nullptr; this->coordinates.key = key;}
};

template <class TreeType, class TreeNodeType>
class TreeDrawer
{
public:
    TreeDrawer()
    {
        scene = nullptr;
    }
    ~TreeDrawer()
    {
        if (scene)
            delete scene;
    }
    QGraphicsScene *draw_tree(TreeType *Tree)
    {
        this->scene = new QGraphicsScene();
        add_coordinates(Tree->root, nullptr, box * pow(2, tree_height(Tree->root) - 1), 0, 0);
        DrawTree(Tree->root, scene);
        return scene;
    }
private:
    QGraphicsScene *scene;
    const int box = 30;
    void add_coordinates(TreeNodeType *root, TreeNodeType *prev, double width, double y, int level)
    {
        int buf = floor(width / pow(2, level));
        if (root != nullptr)
        {
            if (prev == nullptr)
            {
                root->coordinates.x = buf;
                root->coordinates.y = y;
            }
            else
            {
                if (root->coordinates.key == 'l')
                {
                    root->coordinates.x = prev->coordinates.x - buf;
                    root->coordinates.y = prev->coordinates.y + 80;
                }
                else if (root->coordinates.key == 'r')
                {
                    root->coordinates.x = prev->coordinates.x + buf;
                    root->coordinates.y = prev->coordinates.y + 80;
                }
            }
            add_coordinates(root->left, root, width, root->coordinates.y, level + 1);
            add_coordinates(root->right, root, width, root->coordinates.y, level + 1);
        }
    }
    void DrawTree(TreeNodeType *root, QGraphicsScene *scene)
    {
        const int ELLIPSE_WIDTH = 45, ELLIPSE_HEIGHT = 25;
        if (root)
        {
            QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem();
            QGraphicsTextItem *text = new QGraphicsTextItem();
            text->setPlainText(QString::number(root->value));
            text->setTextWidth(text->font().pointSizeF() * text->toPlainText().length() * 2);
            ellipse->setRect(root->coordinates.x, root->coordinates.y, ELLIPSE_WIDTH, ELLIPSE_HEIGHT);
            text->setPos(root->coordinates.x + 12, root->coordinates.y);
            text->setParentItem(ellipse);
            if (root->left)
            {
                QGraphicsLineItem *line1 = new QGraphicsLineItem();
                line1->setParentItem(ellipse);
                line1->setLine(root->coordinates.x + ELLIPSE_WIDTH / 2, root->coordinates.y + ELLIPSE_HEIGHT,
                               root->left->coordinates.x + ELLIPSE_WIDTH / 2, root->left->coordinates.y);
            }
            if (root->right)
            {
                QGraphicsLineItem *line2 = new QGraphicsLineItem();
                line2->setParentItem(ellipse);
                line2->setLine(root->coordinates.x + ELLIPSE_WIDTH / 2, root->coordinates.y + ELLIPSE_HEIGHT,
                               root->right->coordinates.x + ELLIPSE_WIDTH / 2, root->right->coordinates.y);
            }
            scene->addItem(ellipse);
            DrawTree(root->left, scene);
            DrawTree(root->right, scene);
        }
    }
    int tree_height(TreeNodeType *root)
    {
        if (root == nullptr)
            return 0;
        return 1 + std::max(tree_height(root->left), tree_height(root->right));
    }
};

template <class TreeNodeType>
class TreeOut
{
public:
    TreeOut(TreeNodeType *root)
    {
        this->root = root;
    }
    std::string tree_to_str(std::string flag)
    {
        print_result = "";
        if (flag == "inorder")
            inorder(this->root);
        else if (flag == "preorder")
            preorder(this->root);
        else if (flag == "postorder")
            postorder(this->root);
        else
            return "ERROR";
        return print_result;
    }
private:
    TreeNodeType *root;
    std::string print_result;
    void inorder(TreeNodeType *root)
    {
        if (root)
        {
            inorder(root->left);
            print_result += std::to_string(root->value) + '\n';
            inorder(root->right);
        }
    }
    void preorder(TreeNodeType *root)
    {
        if (root)
        {
            print_result += std::to_string(root->value) + '\n';
            preorder(root->left);
            preorder(root->right);
        }
    }
    void postorder(TreeNodeType *root)
    {
        if (root)
        {
            postorder(root->left);
            postorder(root->right);
            print_result += std::to_string(root->value) + '\n';
        }
    }
};

class Tree
{
public:
    tree_node *root;
    Tree()
    {
        root = nullptr;
        drawer = nullptr;
    }
    ~Tree()
    {
        if (root)
            delete_tree(this->root);
        if (drawer)
            delete drawer;
    }
    void generate_tree(int min, int max, int size)
    {
        if (root)
            delete_tree(root);
        root = nullptr;
        std::srand(std::time(nullptr));
        for (int i = 0; i < size; i++)
            this->root = add_new(this->root, min + rand() % (max - min + 1), '#');
    }
    std::string out_tree(std::string flag)
    {
        std::string print_result = "";
        TreeOut<tree_node> *out  = new TreeOut<tree_node>(this->root);
        print_result = out->tree_to_str(flag);
        return print_result;
    }
    QGraphicsScene *draw_tree()
    {
        this->drawer = new TreeDrawer<Tree, tree_node>();
        return drawer->draw_tree(this);
    }
private:
    TreeDrawer<Tree, tree_node> *drawer;
    tree_node *add_new(tree_node *root, int val, char k)
    {
        if (root == nullptr)
            return new tree_node(val, k);
        else if (val < root->value)
            root->left = add_new(root->left, val, 'l');
        else
            root->right = add_new(root->right, val, 'r');
        return root;
    }
    void delete_tree(tree_node *root)
    {
        if (root)
        {
            delete_tree(root->left);
            delete_tree(root->right);
            delete root;
        }
    }
};

class AVL_tree
{
public:
    AVL_tree_node *root;
    AVL_tree()
    {
        this->root = nullptr;
        this->drawer = nullptr;
    }
    ~AVL_tree()
    {
        if (root)
            delete_tree(root);
        if (drawer)
            delete drawer;
    }
    void generate_tree(int min, int max, int size)
    {
        if (root)
            delete_tree(root);
        root = nullptr;
        std::srand(std::time(nullptr));
        for (int i = 0; i < size; i++)
            this->root = add_new(this->root, min + rand() % (max - min + 1), '#');
    }
    std::string out_tree(std::string flag)
    {
        std::string print_result = "";
        TreeOut<AVL_tree_node> *out  = new TreeOut<AVL_tree_node>(this->root);
        print_result = out->tree_to_str(flag);
        delete out;
        return print_result;
    }
    QGraphicsScene *draw_tree()
    {
        this->drawer = new TreeDrawer<AVL_tree, AVL_tree_node>();
        return drawer->draw_tree(this);
    }
private:
    TreeDrawer<AVL_tree, AVL_tree_node> *drawer;
    AVL_tree_node *add_new(AVL_tree_node *root, int val, char k)
    {
        if (root == nullptr)
            return new AVL_tree_node(val, k);
        else if (val < root->value)
            root->left = add_new(root->left, val, 'l');
        else
            root->right = add_new(root->right, val, 'r');
        return balance(root);
    }
    AVL_tree_node *balance(AVL_tree_node *root)
    {
        restore_height(root);
        if (balance_factor(root) == 2)
        {
            if (balance_factor(root->right) < 0)
                root->right = rotate_right(root->right);
            return rotate_left(root);
        }
        if (balance_factor(root) == -2)
        {
            if (balance_factor(root->left) > 0)
                root->left = rotate_left(root->left);
            return rotate_right(root);
        }
        return root;
    }
    AVL_tree_node *rotate_left(AVL_tree_node *node)
    {
        AVL_tree_node *temp = node->right;
        char head_tip = node->coordinates.key;
        node->right = temp->left;
        temp->left = node;
        if (temp->left)
            temp->left->coordinates.key = 'r';
        if (node)
            node->coordinates.key = 'l';
        if (node->right)
            node->right->coordinates.key = 'r';
        if (node->left)
            node->left->coordinates.key = 'l';
        temp->coordinates.key = head_tip;
        restore_height(node);
        restore_height(temp);
        return temp;
    }
    AVL_tree_node *rotate_right(AVL_tree_node *node)
    {
        AVL_tree_node *temp = node->left;
        char head_tip = node->coordinates.key;
        node->left = temp->right;
        temp->right = node;
        if (temp->right)
            temp->right->coordinates.key = 'l';
        if (node)
            node->coordinates.key = 'r';
        if (node->left)
            node->left->coordinates.key = 'l';
        if (node->right)
            node->right->coordinates.key = 'r';
        temp->coordinates.key = head_tip;
        restore_height(node);
        restore_height(temp);
        return temp;
    }
    unsigned height(AVL_tree_node *root)
    {
        return root ? root->height : 0;
    }
    int balance_factor(AVL_tree_node *root)
    {
        return height(root->right) - height(root->left);
    }
    void restore_height(AVL_tree_node *root)
    {
        unsigned height_left = height(root->left);
        unsigned height_right = height(root->right);
        if (height_left > height_right)
            root->height = height_left + 1;
        else
            root->height = height_right + 1;
    }
    void delete_tree(AVL_tree_node *root)
    {
        if (root)
        {
            delete_tree(root->left);
            delete_tree(root->right);
            delete root;
        }
    }
};
