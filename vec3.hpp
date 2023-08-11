#include<iostream>
#include<stdlib.h>
#include<math.h>
using std::sqrt;

// Nesse arquivo vamos criar a classe de vetores para utlizar no nosso p
class vec3 {
    public:
        // Vetor
        double e[3];

        // Funçao de criacao do vetor
        vec3() : e{0,0,0} {}
        vec3 (double e0, double e1, double e2) : e{e0, e1, e2} {}

        // Direcoes ou Cores
        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        // Operadores
        inline const  vec3&   operator+ ()       const {return *this;}
        inline        vec3    operator- ()       const {return vec3(-e[0], -e[1], -e[2]);}
        inline        double  operator[](int i)  const {return e[i];}
        inline        double& operator[](int i)        {return e[i];};

        // Auto-Operadores
        vec3& operator+=(const vec3 &v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator-=(const vec3 &v){
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];
            return *this;
        }

        vec3& operator*=(double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(double t){return *this *= 1/t;}

        // Funcoes de Valores
        double length()         const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
        double squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
};
// Funções Inline de Operacoes e Outros

// Funcao para print
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
// Soma de vetores
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
// Subtracao de vetores
inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
// Multiplicacao de Vetores
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
// Multiplicacao Linear
inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// Criando um alias para pontos e cores:
using point3 = vec3;
using color3 = vec3;

// Funcao para printar as cores
void write_color(std::ostream &out, vec3 pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}