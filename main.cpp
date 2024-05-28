#include "kNN.hpp"
#include <ctime>



/// <summary>
/// ////
/// </summary>

void tc1() {
    List<int>* a = new SLinkedList<int>;
    for (int i = 0; i < 10; i++) { a->push_front(i); }// ok
    for (int i = 0; i < (a->length()); i++) { cout << a->get(i) << " "; } //ok
    cout << endl << a->get(9) << " ";
    a->push_back(11); a->push_back(12);
    cout << endl << a->get(11) << " " << endl;
    a->insert(1, 13);
    a->print();
    a->remove(1);
    a->print();
    a->reverse();
    a->print();
    a->print();
    int* array;
    a->split(array, 1, a->length() - 2);
    for (int i = 0; i < (a->length() - 1 - 1); i++) {
        cout << array[i] << " ";
    }
    a->clear();
    cout << "LIST TEST OK" << endl;

    Dataset datatest; int datacol = 0, datarow = 0;
    datatest.getcolumnName()->print();
    List<int>* b = new SLinkedList<int>;
    for (int i = 0; i < 10; i++) { b->push_front(i); }
    for (int i = 0; i < (b->length()); i++) { cout << b->get(i) << " "; }
    List<int>* c = new SLinkedList<int>;
    for (int i = 0; i < 10; i++) { c->push_back(i); }
    for (int i = 0; i < (c->length()); i++) { cout << c->get(i) << " "; }
    for (int i = 0; i < 10; i++) { datatest.getcolumnName()->push_back("i"); }
    cout << endl << "dataset test fuction" << endl;
    datatest.getData()->push_back(b);
    datatest.getData()->push_back(c);
    datatest.getcolumnName()->print();
    datatest.getData()->print(); //address
    //datatest.getData()->get(0)->print();
   //datatest.getData()->get(1)->print();
    datatest.set_row(2);
    datatest.set_col(10);
    int m, n;  datatest.getShape(m, n);
    cout << m << "x" << n << endl;
    cout << "copy dataset test" << endl;
    Dataset cpydata(datatest);
    cpydata.getData()->push_back(b);
    cpydata.getData()->push_back(c);
    cpydata.set_row(4);

    //cpydata.getcolumnName()->print();
    //cpydata.getData()->print(); //address
    //cpydata.getData()->get(0)->print();
    //cpydata.getData()->get(1)->print();
    //cpydata.getData()->get(2)->print();
    //cpydata.getData()->get(3)->print();
    cpydata.printHead(10, 10);
    int x, y;  cpydata.getShape(x, y);
    cout << x << "x" << y << endl;
    cpydata.printHead(10, 10);
    cpydata.printTail(10, 5);
    cout << "here" << endl;
    cout << "here" << endl;
    cout << "Operator test" << endl;

    Dataset opdata = cpydata;
    opdata.printHead(10, 10);
    int o = 0, p = 0;  opdata.getShape(o, p);
    cout << o << "x" << p << endl;
    opdata.printHead(10, 10);
    opdata.drop(3, 2) ? cout << "da xoa" << endl : cout << "khong xoa" << endl;
    opdata.drop(3, 0, "i") ? cout << "da xoa" << endl : cout << "khong xoa" << endl;
    opdata.printHead(10, 10);
    opdata.getShape(o, p);
    cout << o << "x" << p << endl;

    cout << "here" << endl;
    cout << "here" << endl;

    //////

    cout << endl << endl;
    cout << "kNNTEST" << endl;
    cout << "MNIST_TEST" << endl;
    tc1();

    Dataset dataset;
    dataset.loadFromCSV("C:\\Users\\ASUS\\OneDrive\\Documents\\Project1_DSA\\mnist.csv");
    dataset.printHead(6, 6);
    dataset.printTail(6, 6);
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    feature.printHead();
    feature.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;
    feature.printHead();

    label.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;
    label.printHead();
    label.printHead();
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    cout << "Loading fix" << endl;
    knn.fit(X_train, y_train);
    cout << "Loading y_pred" << endl;
    Dataset y_pred = knn.predict(X_test);
    y_pred.printHead();
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc2() {
    Dataset dataset;
    dataset.loadFromCSV("C:\\Users\\ASUS\\OneDrive\\Documents\\Project1_DSA\\mnist.csv");
    int nRows, nCols;

    kNN knn(1000);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}


int maisna(){
    cout << "Bat dau chay" << endl;
    system("pause");
    Dataset dataset;
    dataset.loadFromCSV("C:\\Users\\ASUS\\OneDrive\\Documents\\Project1_DSA\\mnist.csv");
    //dataset.printHead(6, 6); cout << endl;
    //dataset.printTail(6, 6); cout << endl;
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    //cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    feature.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;
    feature.printHead(); cout<< endl << endl << endl << endl;

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    cout << "khoi  tao bang X_train" << endl;
    X_train.getData()->get(0)->print();
    y_train.getData()->get(0)->print();
    X_test.getData()->get(0)->print();
    y_test.printHead();
    cout << "khoi  tao KNN" << endl;
    cout << "Checking fit" << endl;
    knn.fit(X_train, y_train);
    cout << "Loading y_pred" << endl;
    Dataset y_pred = knn.predict(X_test);
    cout << "Checking y_pred" << endl;
    y_pred.printHead();
    //double accuracy = knn.score(y_test, y_pred);
    //cout << "Accuracy: " << accuracy << endl;
    //system("pause");
    cout << "Loading fix" << endl;
    return 0;
}

void testmain() {   
    
    Dataset dataset;
    dataset.loadFromCSV("C:\\Users\\ASUS\\OneDrive\\Documents\\Project1_DSA\\mnist.csv");
    int nRows, nCols;

    ifstream file("C:\\Users\\ASUS\\Downloads\\BTL1\\TestCase_2\\input\\input803.txt");
    if (!file.is_open())
    {
        cout << "Error: " << endl;
        return;
    }

    cout << "TESSTTTT" << endl;
    string s;
    int value, index, i = 1, number;
    int k = 5;
    double test_size = 0.0;
    while (file >> s)
    {
        if (s == "Dataset")
        {

            cout << "Line " << i << " "
                << "Dataset " << endl;
            Dataset d(dataset);
            d.printHead(100, 100);
        }
        else if (s == "k")
        {
            string temp;
            file >> temp;
            file >> k;
        }
        else if (s == "test_size")
        {
            string temp;
            file >> temp;
            file >> test_size;
        }
        else if (s == "operator=")
        {

            cout << "Line " << i << " "
                << "operator= " << endl;
            Dataset d = dataset;
            d.printHead(100, 100);
        }
        else if (s == "getShape")
        {
            int nRows = 0, nCols = 0;
            dataset.getShape(nRows, nCols);
            cout << "Line " << i << " "
                << "getShape : " << nRows << " " << nCols << endl;
        }
        else if (s == "columns")
        {
            cout << "Line " << i << " "
                << "columns : ";
            dataset.columns();
        }
        else if (s == "printHead")
        {
            int nRows = 0, nCols = 0;
            file >> nRows >> nCols;
            cout << "Line " << i << " "
                << "printHead " << nRows << " " << nCols << endl;
            dataset.printHead(nRows, nCols);
        }
        else if (s == "printTail")
        {
            int nRows = 0, nCols = 0;
            file >> nRows >> nCols;
            cout << "Line " << i << " "
                << "printTail " << nRows << " " << nCols << endl;
            dataset.printTail(nRows, nCols);
        }
        else if (s == "drop")
        {
            int axis = 0, index = 0;
            string columns = "";
            file >> axis >> index >> columns;
            cout << "Line " << i << " "
                << "drop " << axis << " " << index << " " << columns << " : "
                << (dataset.drop(axis, index, columns) ? "true" : "false") << endl;
        }
        else if (s == "extract")
        {
            int startRow, endRow, startCol, endCol;
            file >> startRow >> endRow >> startCol >> endCol;

            cout << "Line " << i << " "
                << "extract " << startRow << " " << endRow << " " << startCol << " " << endCol << endl;
            Dataset d = dataset.extract(startRow, endRow, startCol, endCol);
            d.printHead(100, 100);
        }
        i++;
    }

    
    kNN knn(k);

    Dataset X_train, X_test, y_train, y_test;
    int nCol = 0;
    int nRow = 0;

    dataset.getShape(nRow, nCol);
    
    Dataset feature = dataset.extract(0, -1, 1, nCol);
    
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, test_size, X_train, X_test, y_train, y_test);
    
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    cout << "Line X_train : " << endl;
    X_train.printHead(100, 100);
    cout << "Line X_test : " << endl;
    X_test.printHead(100, 100);
    cout << "Line y_train : " << endl;
    y_train.printHead(100, 100);
    cout << "Line y_test : " << endl;
    y_test.printHead(100, 100);
    cout << "Line y_predict : " << endl;
    y_pred.printHead(100, 100);

    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc1127()
{
    
    int nRows, nCols;

    Dataset dataset;
    dataset.loadFromCSV("C:\\Users\\ASUS\\OneDrive\\Documents\\Project1_DSA\\mnist.csv");
    List<int>* row = dataset.getData()->get(0);
    for (int j = 0; j < 35; j++) {
        for (int i = 0; i < 10000000; i++) {
            row->insert(0, 1);
        }
        cout << j << endl;
        for (int i = 0; i < 10000000; i++) {
            row->remove(0);
        }
    }
    cout << row->length();
}
int main() {
    //testmain();
    
    clock_t start, end; // Khai báo biến thời gian
    double time_used; // Thời gian sử dụng

    start = clock(); // Lấy thời gian trước khi thực hiện thuật toán
    //testmain();
    tc2();
    end = clock(); // Lấy thời gian sau khi thực hiện

    // Tính thời gian chạy
    time_used = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Thời gian chạy : " << time_used << " giây";
   
    return 0;
}
