#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *data;
    size_t size;
} vector;

typedef struct {
    vector **data;
    size_t rows;
    size_t columns;
} matrix;

vector CreateVector(size_t size) {
    vector v;
    v.data = (double *)calloc(size, sizeof(double));
    v.size = size;
    return v;
}

void FreeVector(vector *v) {
    free(v->data);
}

matrix CreateMatrix(size_t row_size, size_t column_size) {
    matrix m;
    m.data = (vector **)calloc(row_size, sizeof(vector *));
    m.rows = row_size;
    m.columns = column_size;

    for (size_t i = 0; i < row_size; i++) {
        m.data[i] = (vector *)calloc(column_size, sizeof(vector));
        for (size_t j = 0; j < column_size; j++){
            m.data[i][j] = CreateVector(column_size);
        }
    }
    
    return m;
}

void FreeMatrix(matrix *m) {
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->columns; j++) {
            FreeVector(&(m->data[i][j]));
        }
        free(m->data[i]);
    }
    free(m->data);
}

vector Convolution(vector *a, vector *b) {
    size_t maxSize = a->size + b->size - 1;
    vector c = CreateVector(maxSize);

    for (size_t i = 0; i < a->size; ++i) {
        for (size_t j = 0; j < b->size; ++j) {
            c.data[i + j] += a->data[i] * b->data[j];
        }   
    }

    return c;
}

vector PolynominalConstruct(vector *e) {
    vector c = CreateVector(e->size + 1);
    c.data[0] = 1.0;

    for (size_t j = 0; j < e->size; ++j) {
        for (size_t i = j + 1; i > 0; --i) {
            c.data[i] -= e->data[j] * c.data[i - 1];
        }
    }

    return c;
}

vector NewtonInterpolation(vector *x, vector *y) {
    matrix d = CreateMatrix(x->size, y->size);

    for (size_t i = 0; i < y->size; ++i) {
        d.data[i]->data[0] = y->data[i];
    }

    for (size_t j = 1; j < x->size; ++j) {
        for (size_t k = j; k < x->size; ++k) {
            double *dkj = &d.data[k]->data[j];

            double dkjm1 = d.data[k]->data[j - 1];
            double dkm1jm1 = d.data[k - 1]->data[j - 1];
            double xk = x->data[k];
            double xkmj = x->data[k - j];

            *dkj = (dkjm1 - dkm1jm1) / (xk - xkmj);
        }
    }

    vector c;
    c.size = 1;
    c.data = &d.data[x->size - 1]->data[y->size - 1];

    for (int k = x->size - 2; k >= 0; --k) {
        vector e;
        e.size = 1;
        e.data = &x->data[k];

        vector poly = PolynominalConstruct(&e);
        vector tempC = Convolution(&c, &poly);
        FreeVector(&poly);

        tempC.data[tempC.size - 1] += d.data[k]->data[k];

        c = tempC;
    }

    FreeMatrix(&d);

    return c;
}

int main(int argc, const char **argv) {
    int num_points = (argc - 1) / 2;
    double *xTab = (double *)malloc(num_points * sizeof(double));
    double *yTab = (double *)malloc(num_points * sizeof(double));

    for (int i = 1; i <= num_points; ++i) {
        double val = atof(argv[i]);
        xTab[i-1] = val;
    }

    int j = 0;
    for (int i = num_points + 1; i < argc; ++i) {
        double val = atof(argv[i]);
        yTab[j++] = val;
    }

    vector x;
    x.size = 4;
    x.data = xTab;

    vector y;
    y.size = 4;
    y.data = yTab;

    vector c = NewtonInterpolation(&x, &y);

    for (int i = 0; i < c.size; ++i) {
        printf("%f, ", c.data[i]);
    }

    printf("\n");

    FreeVector(&c);

    return 0;
}