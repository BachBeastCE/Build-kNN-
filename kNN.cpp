#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */


 //LINKED LIST TEST

template <class T>
SLinkedList<T>::Node::Node() : data{}, next{ nullptr } {}
//ok

template <class T>
SLinkedList<T>::Node::~Node() {
    next = nullptr;
}//ok
//ok

template <class T>
SLinkedList<T>::~SLinkedList() {
    clear();
}//ok
//ok

template <class T>
void SLinkedList<T>::push_back(T value) {
    Node* newNode = new Node();
    newNode->data = value;
    if (head == nullptr) {
        head = newNode;
    }
    else {
        tail->next = newNode;
    }
    tail = newNode;
    count++;
}//ok
//ok

template <class T>
void SLinkedList<T>::push_front(T value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    if (count == 0) {
        tail = head;
    }
    count++;
}//ok
//ok

template <class T>
void SLinkedList<T>::insert(int index, T value) {
    if (index < 0 || index > length()) {
        return;
        //throw std::out_of_range("get(): Out of range");
    }
    else if (index == 0) {
        push_front(value);
    }
    else if (index == length()) {
        push_back(value);
    }
    else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = current->next;
        current->next = newNode;
        if (newNode->next == nullptr) {
            tail = newNode;
        }
        count++;
    }
}
//ok

template <class T>
void SLinkedList<T>::remove(int index) {
    if (index < 0 || index >= length()) {
        return;
        //throw std::out_of_range("get(): Out of range");
    }
    else if (count == 1) {
        delete head;
        head = tail = nullptr;
    }
    // xoa dau
    else if (index == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    // xoa 1 phan tu
    else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = current->next->next;
        if (temp == tail) {
            tail = current;
        }
        delete temp;
    }
    count--;
}
//

template <class T>
T& SLinkedList<T>::get(int index) const {
    if (index < 0 || index >= length()) {
        throw std::out_of_range("get(): Out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}
//ok

template <class T>
int SLinkedList<T>::length() const {
    return count;
}
//ok

template <class T>
void SLinkedList<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

template <class T>
void SLinkedList<T>::print() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) { cout << " "; }
        current = current->next;
    }
}
//ok

template <class T>
void SLinkedList<T>::reverse() {
    Node* current = head;
    Node* previous = nullptr;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    head = previous;
}
//ok

template <class T>
void SLinkedList<T>::split(T*& target, int begin_idx, int end_idx) const {
    int m = length();
    if (begin_idx < 0 || end_idx > length() || begin_idx > end_idx) {
        throw std::out_of_range("get(): Out of range");
    }
    int size = end_idx - begin_idx + 1;
    if (size <= 0) {
        //target = nullptr;
        return;
    }
    Node* current = head;
    for (int i = 0; i < begin_idx; i++) {
        current = current->next;
    }
    target = new T[size + 5];
    for (int i = 0; i < size; i++) {
        target[i] = current->data;
        current = current->next;
    }
}
//ok

////////____DATASET

Dataset::Dataset() {
    this->data = new SLinkedList<List<int>*>;
    columnName = new SLinkedList<string>;
    numRows = 0;
    numCols = 0;
}
//ok

Dataset::~Dataset() {
    //   cout << "call destructor dataset" << endl;
    delete this->data; this->data = nullptr;
    delete this->columnName; this->columnName = nullptr;
    numRows = 0;
    numCols = 0;
}
//maybe

Dataset::Dataset(const Dataset& other) {
    //getshape
    int col, row; other.getShape(row, col);
    this->numCols = col; this->numRows = row;
    //this->set_row(row); this->set_col(col);
    //copy column
    string* cpystring = nullptr;
    this->columnName = new SLinkedList<string>;
    if (col != 0 || row != 0) {
        other.getcolumnName()->split(cpystring, 0, col - 1);
    }
    if (cpystring) {
        for (int i = 0; i < col; i++)
        {
            this->columnName->push_back(cpystring[i]);
        }
    }

    //copydata
    this->data = new SLinkedList<List<int>*>;
    int** cpydata = nullptr;
    other.make_table(cpydata, 0, row - 1, 0, col - 1);
    for (int i = 0; i < row; i++)
    {
        List<int>* newrow = new SLinkedList<int>;
        for (int j = 0; j < col; j++)
        {
            newrow->push_back(cpydata[i][j]);
        }
        this->data->push_back(newrow);
    }
}
//maybe

Dataset& Dataset::operator=(const Dataset& other) {
    //getshape
    //int col, row; other.getShape(row, col);
    this->numCols = other.numCols; this->numRows = other.numRows;
    //this->set_row(row); this->set_col(col);
   // cout << row << " " << col;

    //copy column
    if (other.columnName != nullptr) {
        //cout << " copy du lieu columname " << endl;
        string* cpystring = nullptr;
        this->columnName = new SLinkedList<string>;
        if (this->numCols != 0 || this->numRows != 0) {
            other.getcolumnName()->split(cpystring, 0, this->numCols - 1);
        }
        if (cpystring) {
            for (int i = 0; i < this->numCols; i++)
            {
                this->columnName->push_back(cpystring[i]);
            }
        }
    }
    //copydata
    if (other.data != nullptr) {
        //cout << " copy du lieu data " << endl;
        this->data = new SLinkedList<List<int>*>;
        int** cpydata = nullptr;
        other.make_table(cpydata, 0, this->numRows - 1, 0, this->numCols - 1);
        for (int i = 0; i < this->numRows; i++)
        {
            List<int>* newrow = new SLinkedList<int>;
            for (int j = 0; j < this->numCols; j++)
            {
                newrow->push_back(cpydata[i][j]);
            }
            this->data->push_back(newrow);
        }
    }
    return *this;
}
//maybe

bool Dataset::loadFromCSV(const char* fileName) {
    //Open file
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false; // Unable to open file
    }
    // Get Columname
    std::string line;
    std::getline(file, line);
    std::stringstream ss1(line);
    List<string>* row = new SLinkedList<string>;
    std::string value1;
    while (std::getline(ss1, value1, ',')) {
        columnName->push_back(value1);
    }
    //Get data
    while (std::getline(file, line)) {
        std::stringstream ss2(line);
        List<int>* row = new SLinkedList<int>;
        std::string value2;
        while (std::getline(ss2, value2, ',')) {
            row->push_back(std::stoi(value2));
        }
        data->push_back(row);
    }

    //update colnum and rownum
    numRows = data->length();
    numCols = (numRows > 0) ? data->get(0)->length() : 0;

    //close and return
    file.close();
    return true;
}
//ok

void Dataset::printHead(int nRows, int nCols) const {
    if (nRows < 0 || nCols < 0) {
        return;
    }
    nRows = min(nRows, this->numRows);
    nCols = min(nCols, this->numCols);

    // Print column names
    for (int j = 0; j < nCols; j++) {
        cout << columnName->get(j);
        if (j != nCols - 1) cout << ' ';
    }
    cout << endl;

    // Print data rows
    for (int i = 0; i < nRows; i++) {
        //cout << "row" << i + 1 << ":";
        List<int>* row = data->get(i);
        for (int j = 0; j < nCols; j++) {
            cout << row->get(j);
            if (j != nCols - 1) cout << ' ';
        }
        if (i != nRows - 1) { cout << endl; }
    }
}
//ok

void Dataset::printTail(int nRows, int nCols) const {
    if (nRows < 0 || nCols < 0) {
        return;
    }

    nRows = min(nRows, this->numRows);
    nCols = min(nCols, this->numCols);

    // Print column names
    for (int j = numCols - nCols; j < numCols; j++) {
        cout << columnName->get(j);
        if (j != numCols - 1) cout << ' ';
    }
    cout << endl;
    // Print data rows
    for (int i = numRows - nRows; i < numRows; i++) {
        List<int>* row = data->get(i);
        for (int j = numCols - nCols; j < numCols; j++) {
            cout << row->get(j);
            if (j != numCols - 1)  cout << ' ';
        }
        if (i != numRows - 1) { cout << endl; }
    }
}
//ok

void Dataset::getShape(int& nRows, int& nCols) const {
    nRows = this->numRows;
    nCols = this->numCols;
}
//ok

void Dataset::columns() const {
    if (this->columnName) { this->columnName->print(); }
}
//ok

bool Dataset::drop(int axis, int index, std::string columns) {
    if (axis == 0) {
        if (index >= 0 && index < this->numRows) {
            data->get(index)->clear();
            data->remove(index);
            this->set_row(this->numRows - 1);
            return true;
        }
    }
    if (axis == 1) {
        if (this->columnName != nullptr && this->numCols > 0) {
            int columnIndex = -1;
            string* getcolname = nullptr;
            columnName->split(getcolname, 0, this->numCols - 1);
            for (int j = 0; j < this->numCols; j++) {
                if (columns == getcolname[j]) {
                    columnIndex = j;
                    break;
                }
            }
            if (columnIndex >= 0) {
                this->columnName->remove(columnIndex);
                for (int i = 0; i < numRows; i++) {
                    this->data->get(i)->remove(columnIndex);
                }
                this->set_col(this->numCols - 1);
                return true;
            }
        }
    }
    return false;
}
//maybe

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    // Calculate the number of rows and columns to extract
    // Create a new dataset to store the extracted data

    Dataset extractedData;
    if (endRow == -1 || endRow == this->numRows) {
        endRow = this->numRows - 1;
    }
    endRow = min(endRow, numRows - 1);
    if (endCol == -1 || endCol == this->numCols)
    {
        endCol = this->numCols - 1;
    }
    endCol = min(endCol, numCols);

    if (startRow < 0 || startRow > endRow) {
        throw std::out_of_range("get(): Out of range");
    }
    if (startCol < 0 || startCol > endCol) {
        throw std::out_of_range("get(): Out of range");
    }
    if (endRow < -1 || endRow > this->numRows) {
        throw std::out_of_range("get(): Out of range");
    }
    if (endCol < -1 || endCol > this->numCols) {
        throw std::out_of_range("get(): Out of range");
    }
    //cout << " tinh toan size" << endl;

    extractedData.numCols = endCol - startCol + 1;
    extractedData.numRows = endRow - startRow + 1;


    if (extractedData.numCols <= 0 || extractedData.numRows <= 0) {
        throw std::out_of_range("get(): Out of range");
    }
    else
    {
        //cout << " khoi  tao bang colname" << endl;
        //update column name
        string* getcolname = nullptr;
        columnName->split(getcolname, startCol, endCol);

        for (int i = 0; i < extractedData.numCols; i++)
        {
            extractedData.columnName->push_back(getcolname[i]);
        }
        if (getcolname != nullptr) { delete[] getcolname; }

        //cout << "khoi  tao bang data" << endl;
        //update data
        int** cpydata = nullptr;
        this->make_table(cpydata, startRow, endRow, startCol, endCol);

        for (int i = 0; i < extractedData.numRows; i++)
        {
            List<int>* newrow = new SLinkedList<int>;
            for (int j = 0; j < extractedData.numCols; j++)
            {
                newrow->push_back(cpydata[i][j]);
            }
            extractedData.data->push_back(newrow);
        }
        // giai phong bo nho
        for (int i = 0; i < extractedData.numRows; i++) {
            delete[] cpydata[i]; cpydata[i] = nullptr;
        }
        delete[]cpydata; cpydata = nullptr;
    }

    //extractedData.printHead(2, 120); cout << endl;
    return extractedData;
}

List<List<int>*>* Dataset::getData() const {
    return this->data;
}
//ok

List<string>* Dataset::getcolumnName() const {
    return this->columnName;
}
//ok

void Dataset::make_table(int**& target_table, int row_begin_idx, int row_end_idx, int col_begin_idx, int col_end_idx) const {
    int numRows, numCols; this->getShape(numRows, numCols);

    int numcol_array = col_end_idx - col_begin_idx + 1;
    int numrow_array = row_end_idx - row_begin_idx + 1;

    if (numcol_array <= 0 || numrow_array <= 0 ||
        row_end_idx >= numRows || col_end_idx >= numCols ||
        row_begin_idx < 0 || col_begin_idx < 0) {
        return;
    }
    else
    {
        target_table = new int* [numrow_array];
        List<int>** getrowdata = nullptr;
        int* getcoldata = nullptr;
        this->data->split(getrowdata, row_begin_idx, row_end_idx);
        for (int i = 0; i < numrow_array; i++)
        {
            getrowdata[i]->split(getcoldata, col_begin_idx, col_end_idx);
            target_table[i] = getcoldata;
        }
    }
}
//maybe

////////___KNN

kNN::kNN(int k) {
    this->k = k;
    x_train_data = nullptr;
    y_train_data = nullptr;
    x_train_numcol = 0;
    x_train_numrow = 0;
    y_train_numcol = 1;
}
//ok

void kNN::fit(const Dataset& x_train, const Dataset& y_train) {
    /*
    * Thực hiện tải dữ liệu để huấn luyện, trong đó:
    – X_train: Bảng dữ liệu chứa các đặc trưng không phải là nhãn. Số hàng của X_train là số lượng ảnh được sử dụng để huấn luyện, và số cột là số đặc trưng.
    – y_train: Bảng dữ liệu chứa các nhãn tương ứng với các đặc trưng. Vì chỉ là các nhãn, nên số hàng của y_train là số lượng ảnh, và số cột chỉ duy nhất là 1.
    */

    //copy data cua x_train sang mang 2 chieu
    x_train.getShape(this->x_train_numrow, this->x_train_numcol);
    x_train.make_table(this->x_train_data, 0, x_train_numrow - 1, 0, x_train_numcol - 1);
    y_train.make_table(this->y_train_data, 0, x_train_numrow - 1, 0, 0);
}
//maybe


// check laij
Dataset kNN::predict(const Dataset& x_test) {
    Dataset y_predict;
    y_predict.getcolumnName()->push_back("label");
    int** x_test_data = nullptr;
    int x_test_numrow, x_test_numcol; x_test.getShape(x_test_numrow, x_test_numcol);
    x_test.make_table(x_test_data, 0, x_test_numrow - 1, 0, x_test_numcol - 1);
    y_predict.set_row(x_test_numrow);
    y_predict.set_col(1);
    if (k > x_train_numrow)throw std::out_of_range("get(): Out of range");
    
    // Predition 
    for (int i = 0; i < x_test_numrow; i++)
    {
        //save cap distance_label
        pair<double, int>* distance_label = new pair<double, int>[x_train_numrow + 1];

        // tinh khoang cach euclide den tung so
        double Euclide_distance = 0;
        for (int j = 0; j < x_train_numrow; j++)
        {
            for (int c = 0; c < x_test_numcol; c++)
            {
                Euclide_distance += pow(x_test_data[i][c] - x_train_data[j][c], 2);
            }
            double rounded_number = round(sqrt(Euclide_distance) * 10000000000) / 10000000000;
            Euclide_distance = rounded_number;

            distance_label[j].first = Euclide_distance;
            distance_label[j].second = y_train_data[j][0];
        }
        //sap xep cac cap pair
        //pair_quick_sort(distance_label, 0, x_train_numrow - 1);
        bubbleSort(distance_label, x_train_numrow);

        /*
                for (int i = 0; i < k; i++)
        {
            cout<<distance_label[i].second<<" ";
        }
        */
        

        // lay k phan tu gan nhat;
        int num[10] = { 0,0,0,0,0,0,0,0,0,0 }; // mang index tu 0-9
        for (int i = 0; i < k; i++)
        {
            num[distance_label[i].second] += 1;
        }
        // tim phan tu gan nhat co so luong nhieu nhat trong k phan tu gan nhat

        //
        /*

                    if (num[i] == max && i != max_index ) {
                for (int j = 0; j < k; i++)
                {
                    if (distance_label[j].second == max_index) { break; }
                    else if (distance_label[j].second == i) { max_index = i; }
                }
            }
        */



        // Find the most frequent label

        int max = num[0];
        int max_index = 0;
        for (int i = 1; i < 10; ++i) {
            if (num[i] > max) {
                max = num[i]; max_index = i;
            }
            //else if (num[i] == max) { same_max.push_back(i); many_max_element = 1; }
        }
        // neu co truong hop trung nhau
        /*
                if (many_max_element) {
            for (int i = 0; i < k; i++)
            {
                for (int j = 0; j < same_max.length(); j++)
                {
                    if (distance_label[i].second == same_max.get(j)) {
                        max_index = same_max.get(j);
                        many_max_element = false;
                        break;
                    }
                }
                if (many_max_element == false) { break; }
            }
        }
        */



        //push vao predict list
        //cout << max_index << endl;
        SLinkedList<int>* newrow = new SLinkedList<int>; newrow->push_back(max_index);
        y_predict.getData()->push_back(newrow);
    }
    //y_predict.printHead();


    //giai phong bo nho
    for (int i = 0; i < x_test_numrow; i++) { delete x_test_data[i]; }
    delete x_test_data;

    // tra ket qua;
    //y_predict.printHead(10);
    return y_predict;
}

double kNN::score(const Dataset& y_test, const Dataset& y_pred) {
    int y_test_numrow, y_test_numcol; y_test.getShape(y_test_numrow, y_test_numcol);

    //int** y_test_data = nullptr;
    //int** y_pred_data = nullptr;
    //y_test.make_table(y_test_data, 0, y_test_numrow - 1, 0, 0);
    //y_pred.make_table(y_pred_data, 0, y_test_numrow - 1, 0, 0);
   // int y_pest_numrow, y_pest_numcol; y_pred.getShape(y_test_numrow, y_test_numcol);

    double sum = 0;
    for (int i = 0; i < y_test_numrow; i++)
    {
        if (y_test.getData()->get(i)->get(0) == y_pred.getData()->get(i)->get(0)) { sum += 1.0; }
    }

    // gia phong bo nho
    /*
        for (int i = 0; i < y_test_numrow; i++) {
        delete y_test_data[i]; y_test_data[i] = nullptr;
        delete y_pred_data[i]; y_pred_data[i] = nullptr;
    }
    y_test_data = nullptr;
    */
    // tra ket qua
    double num = sum / y_test_numrow;
    //double rounded_number = round(num * 1000) / 1000;
    return num;// rounded_number;
}

/////split___sort

void train_test_split(Dataset& X, Dataset& Y, double test_size,
    Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test) {
    int x_numrow, x_numcol; X.getShape(x_numrow, x_numcol);
    //cout << x_numrow << "x" << x_numcol << endl;
    int y_numrow, y_numcol; Y.getShape(y_numrow, y_numcol);
    //cout << y_numrow << "x" << y_numcol << endl;
    int train_count = int(x_numrow * (1 - test_size));
    //cout << train_count << endl;
    X_train = X.extract(0, train_count - 1, 0, -1);
    //X_train.printHead();
    X_test = X.extract(train_count, x_numrow - 1, 0, -1);
    //X_test.printHead();
    y_train = Y.extract(0, train_count - 1, 0, -1);
    //y_train.printHead();
    y_test = Y.extract(train_count, x_numrow - 1, 0, -1);
    //y_test.printHead();
    return;
}
//ok

void bubbleSort(pair<double, int>*& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].first > arr[j + 1].first) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


