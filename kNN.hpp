#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual void split(T* &target, int begin_idx = 0, int end_idx = 0) const = 0;
};

template <class T>
class SLinkedList : public List<T> {
public:         
    class Node;// Forward declaration of the Node class 
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList() : head(NULL), tail(NULL), count(0) {};
    ~SLinkedList();
    void push_back(T value) override;
    void push_front(T value) override;
    void insert(int index, T value) override;
    void remove(int index) override;
    T& get(int index) const override;
    int length() const override;
    void clear() override;
    void print() const override;
    void reverse() override;
    void split(T*& target, int begin_idx = 0, int end_idx = 0) const override;
public:
    class Node {
    protected:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node();
        ~Node();
    };
};



class Dataset {
private:
    List<List<int>*>* data;
    List<string>* columnName;
    //row_idx max = numRows -1
    //col_idx max = numCols -1
    //You may need to define more
    int numRows ;
    int numCols ;
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    List<List<int>*>* getData() const;
    List<string>* getcolumnName() const;
    void make_table(int** &target_table, int row_begin_index, int row_end_index, int col_begin_index, int col_end_index) const;
    void set_row(int nRows) { numRows = nRows; }
    void set_col(int nCols) { numCols = nCols; }

};

class kNN {
private:
    int k;
    //You may need to define more
    int** x_train_data;
    int** y_train_data;
    int x_train_numcol;
    int x_train_numrow;
    int y_train_numcol;
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

int partition(pair<double, int>* a, int l, int r);
void pair_quick_sort(pair<double, int>* a, int l, int r);

void bubbleSort(pair<double, int>*& arr, int n);

// Please add more or modify as needed


