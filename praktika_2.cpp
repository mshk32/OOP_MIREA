#include <iostream>

using namespace std;

class MyArrayParent
{
protected:
    // сколько памяти выделено?
    int capacity;
    // количество элементов - сколько памяти используем
    int count;
    // массив
    double *ptr;

public:
    // конструкторы и деструктор
    MyArrayParent(int Dimension = 100)
    {
        cout << "\nMyArray constructor";
        ptr = new double[Dimension];
        capacity = Dimension;
        count = 0;
    }
    // конструктор принимает существующий массив
    MyArrayParent(double *arr, int len)
    {
        cout << "\nMyArray constructor";
		ptr = new double[len];
		capacity = len;
		count = len;
		for (int i = 0; i < len; ++i)
			ptr[i] = arr[i];
    }
    // конструктор копий
    MyArrayParent(const MyArrayParent &V)
    {
        cout << "\nCopy constructor";
        // создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
        capacity = V.capacity;
		count = V.count;
		ptr = new double[capacity];
		for (int i = 0; i < count; ++i)
			*(ptr + i) = *(V.ptr + i);
    }
    // деструктор
    ~MyArrayParent()
    {
        cout << "\nMyArray destructor";
        if (ptr != NULL)
        {
            delete[] ptr;
            ptr = NULL;
        }
    }
    // обращение к полям
    int Capacity() { return capacity; }
    int Size() { return count; }
    double GetComponent(int index)
    {
        if (index >= 0 && index < count)
            return ptr[index];
        // сгенерировать исключение, если индекс неправильный
        return -1;
    }
    void SetComponent(int index, double value)
    {
        if (index >= 0 && index < count)
            ptr[index] = value;
        else
            cout << "Error in SetComponent().\n";
    }
    // добавление в конец нового значения
    void push(double value)
    {
        if (count < capacity)
        {
            ptr[count] = value;
            count++;
        }
        // что делаем, если массив заполнен?
        else
            cout << "Error in push(). Array is full.\n";
    }
    // удаление элемента с конца
    void RemoveLastValue()
    {
        if (count >= 0)
            count--;
        // что делаем, если пуст?
        else
            cout << "Error in RemoveLastValue(). Array is empty.\n";
    }
    double &operator[](int index)
    {
        // перегрузка оператора []
        if (index >= 0 && index < count) 
            return ptr[index];
        else if (index >= count && index < capacity) {
            for (int i = count; i <= index; ++i)
                this -> push(0);
            return ptr[index];
        }
        else {
            cout << "Index error.\n";
            return ptr[0];
        }
    }
    MyArrayParent &operator=(const MyArrayParent &V)
    {
        cout << "\noperator = ";
        // оператор =
        // arr1 = arr2 = arr3; где arr_i - объекты нашего класса
        if (capacity != V.capacity) {
            delete[] ptr;
			ptr = new double[V.capacity];
            capacity = V.capacity;
        }
        count = V.count;

        for (int i = 0; i < count; ++i)
            ptr[i] = V.ptr[i];
        return *this;
    }

    void print()
    {
        cout << "\nMyArr, size: " << count << ", values: {";
        int i = 0;
        for (i = 0; i < count; i++)
        {
            cout << ptr[i];
            if (i != count - 1)
                cout << ", ";
        }
        cout << "}";
    }

    int IndexOf(double value) {
        for (int i = 0; i < count; ++i)
            if (abs(ptr[i] - value) < 0.0001)
                return i;
        return -1;
    }
};

enum SurfaceType {
    ELLIPSOID,
    HYPERBOLOID_ONE_SHEET,
    HYPERBOLOID_TWO_SHEETS,
    PARABOLOID_ELLIPTIC,
    PARABOLOID_HYPERBOLIC,
    ELLIPTIC_CONE,
    ELLIPTIC_CYLINDER,
    HYPERBOLIC_CYLINDER,
    PARABOLIC_CYLINDER,
    PLANE,
    UNKNOWN
};

class MyArrayChild : public MyArrayParent
{
public:
    // используем конструктор родителя
    MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension)
    {
        cout << "\nMyArrayChild constructor";
    }
    ~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

    // удаление элемента
    void RemoveAt(int index = -1) {
        if (index == -1) {
            RemoveLastValue();
            return;
        }
        if (index < 0 || index >= count || count == 0) {
            cout << "Index error in RemoveAt().\n";
            return;
        }
        for (index; index < count - 1; ++index)
            ptr[index] = ptr[index + 1];
        --count;
    }

    // вставка элемента
    void InsertAt(double value, int index = -1) {
        if (index == -1) {
            push(value);
            return;
        }
        if (index < 0 || index >= count || count == 0) {
            cout << "Index error in RemoveAt().\n";
            return;
        }

        for (int i = count; i > index; --i)
            ptr[i] = ptr[i - 1];
        
        ptr[index] = value;

		if (count < capacity)
			++count;
    }

    // выделение подпоследовательности
    MyArrayChild SubSequence(int StartIndex = 0, int Length = -1) {
        MyArrayChild result(Length);
        if (Length < 1 || count == 0 || Length > count - StartIndex) {
            cout << "Error in SubSequence().\n";
            return result;
        }

        for (int i = StartIndex; Length > 0; --Length)
            result.push(ptr[i]);
        return result;
    }

    // добавление элемента в конец
    // operator +
    MyArrayChild& operator+(double value)
	{
		if (count < capacity)
			this->push(value);
		return *this;
	}

    SurfaceType DetermineSurfaceType()
    {
        if (count != 10) {
            cout << "Error: Array must have exactly 10 elements to determine the surface type.\n";
            return UNKNOWN;
        }

        double A = ptr[0];
        double B = ptr[1];
        double C = ptr[2];
        double D = ptr[3];
        double E = ptr[4];
        double F = ptr[5];
        double G = ptr[6];
        double H = ptr[7];
        double I = ptr[8];
        double J = ptr[9];

        // Определяем тип поверхности
        if (A != 0 && B != 0 && C != 0 && D == 0 && E == 0 && F == 0) {
            if (A == B && B == C)
                return ELLIPSOID;
            else if ((A == B && C < 0) || (B == C && A < 0) || (A == C && B < 0))
                return HYPERBOLOID_ONE_SHEET;
            else if ((A == B && C > 0) || (B == C && A > 0) || (A == C && B > 0))
                return HYPERBOLOID_TWO_SHEETS;
        } else if (A != 0 && B != 0 && C == 0 && D == 0 && E == 0 && F == 0) {
            return ELLIPTIC_CYLINDER;
        } else if (A != 0 && B == 0 && C != 0 && D == 0 && E == 0 && F == 0) {
            return HYPERBOLIC_CYLINDER;
        } else if (A != 0 && B != 0 && C == 0 && D == 0 && E == 0 && F == 0) {
            return PARABOLIC_CYLINDER;
        } else if (A != 0 && B != 0 && C == 0 && D == 0 && E == 0 && F != 0) {
            return PARABOLOID_ELLIPTIC;
        } else if (A != 0 && B == 0 && C != 0 && D == 0 && E == 0 && F != 0) {
            return PARABOLOID_HYPERBOLIC;
        } else if (A != 0 && B == 0 && C == 0 && D == 0 && E == 0 && F == 0) {
            return PLANE;
        } else {
            return UNKNOWN;
        }
    }

};

class MySortedArray : public MyArrayChild
{
public:
    MySortedArray(int Dimension = 100) : MyArrayChild(Dimension)
    {
        cout << "\nMySortedArray constructor";
    }

    ~MySortedArray() { cout << "\nMySortedArray destructor\n"; }

    SurfaceType DetermineSurfaceType()
    {
        if (count != 10) {
            cout << "Error: Array must have exactly 10 elements to determine the surface type.\n";
            return UNKNOWN;
        }

        // Поскольку массив отсортирован, предположим, что он отсортирован по коэффициентам A, B, C, D, E, F, G, H, I, J
        double A = ptr[0];
        double B = ptr[1];
        double C = ptr[2];
        double D = ptr[3];
        double E = ptr[4];
        double F = ptr[5];
        double G = ptr[6];
        double H = ptr[7];
        double I = ptr[8];
        double J = ptr[9];

        // Логика определения типа поверхности остается такой же
        if (A != 0 && B != 0 && C != 0 && D == 0 && E == 0 && F == 0) {
            if (A == B && B == C)
                return ELLIPSOID;
            else if ((A == B && C < 0) || (B == C && A < 0) || (A == C && B < 0))
                return HYPERBOLOID_ONE_SHEET;
            else if ((A == B && C > 0) || (B == C && A > 0) || (A == C && B > 0))
                return HYPERBOLOID_TWO_SHEETS;
        } else if (A != 0 && B != 0 && C == 0 && D == 0 && E == 0 && F == 0) {
            return ELLIPTIC_CYLINDER;
        } else if (A != 0 && B == 0 && C != 0 && D == 0 && E == 0 && F == 0) {
            return HYPERBOLIC_CYLINDER;
        } else if (A != 0 && B != 0 && C == 0 && D == 0 && E == 0 && F == 0) {
            return PARABOLIC_CYLINDER;
        } else if (A != 0 && B != 0 && C == 0 && D == 0 && E == 0 && F != 0) {
            return PARABOLOID_ELLIPTIC;
        } else if (A != 0 && B == 0 && C != 0 && D == 0 && E == 0 && F != 0) {
            return PARABOLOID_HYPERBOLIC;
        } else if (A != 0 && B == 0 && C == 0 && D == 0 && E == 0 && F == 0) {
            return PLANE;
        } else {
            return UNKNOWN;
        }
    }

    void push(double value)
    {
        if (count >= capacity) {
            cout << "Error in push(). Array is full.\n";
            return;
        }

        int i = count - 1;

        // Сдвигаем элементы массива, чтобы освободить место для нового элемента
        while (i >= 0 && ptr[i] > value) {
            ptr[i + 1] = ptr[i];
            i--;
        }

        ptr[i + 1] = value;
        count++;
    }

    int IndexOf(double value)
    {
        // Используем бинарный поиск, поскольку массив отсортирован
        int left = 0, right = count - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (abs(ptr[mid] - value) < 0.0001)
                return mid;
            if (ptr[mid] < value)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1; // Если элемент не найден
    }
};



int main()
{
    double coefficients[] = {1, 1, 1, 0, 0, 0, 0, 0, 0, -1};
    MyArrayChild array(10);

    for (int i = 0; i < 10; ++i)
        array.push(coefficients[i]);

    SurfaceType type = array.DetermineSurfaceType();

    switch (type) {
        case ELLIPSOID: cout << "Ellipsoid\n"; break;
        case HYPERBOLOID_ONE_SHEET: cout << "Hyperboloid of one sheet\n"; break;
        case HYPERBOLOID_TWO_SHEETS: cout << "Hyperboloid of two sheets\n"; break;
        case PARABOLOID_ELLIPTIC: cout << "Elliptic paraboloid\n"; break;
        case PARABOLOID_HYPERBOLIC: cout << "Hyperbolic paraboloid\n"; break;
        case ELLIPTIC_CONE: cout << "Elliptic cone\n"; break;
        case ELLIPTIC_CYLINDER: cout << "Elliptic cylinder\n"; break;
        case HYPERBOLIC_CYLINDER: cout << "Hyperbolic cylinder\n"; break;
        case PARABOLIC_CYLINDER: cout << "Parabolic cylinder\n"; break;
        case PLANE: cout << "Plane\n"; break;
        default: cout << "Unknown surface type\n"; break;
    }


    return 0;
}