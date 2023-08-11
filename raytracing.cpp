#include "ray.hpp"

// Funcao para a insercao de uma esfera
double hitSphere(const point3& center, double radius, const Ray& r) {
    // Passamos o ponto central dela, juntamente com o raio (dimensao) e o raio de luz
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    // Vamos aplicar a proriedade de normalizacao agora
    if (discriminant < 0) {return -1.0;}
    else {return ((-b - sqrt(discriminant) ) / (2.0*a));}
}

color3 rayColor(const Ray& r){
    double e = hitSphere(point3(0,0,-1), 0.5, r);
    if (e > 0.0){ // Estamos criando aqui uma esfera, na funcao ele vai verificar 
        vec3 N = unit_vector(r.pointAtParameter(e) - vec3(0,0,-1));
        return 0.5*color3(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color3(1.0, 1.0, 1.0) + a*color3(0.5, 0.7, 1.0);
}

int main(){
    // Proporcao e Dimensoes
    double aspectRatio = 1.7777778; // Proporcao da Imagem
    int imgWidth = 400; // Largura da Imagem
    int imgHeight = static_cast<int>(imgWidth / aspectRatio); // Calculando a altura

    // Camera
    double focalLength = 1.0;
    double viewportHeigth = 2.0;
    auto viewportWidth = viewportHeigth * (
        static_cast<double>(imgWidth)/imgHeight);
    auto cameraCenter = point3(0,0,0);
    
    // Vetores nas arestas horizontais e verticais da viewport
    auto viewportU = vec3(viewportWidth, 0, 0);
    auto viewportV = vec3(0,-viewportHeigth, 0);

    // Calculando os vetores delta horizontais e veerticais pixel a pixel
    auto pixelDeltaU = viewportU / imgWidth;
    auto pixelDeltaV = viewportV / imgHeight;

    // Calculando a localizacao do pixel mas à esquerda e superior
    auto viewportUL = cameraCenter - vec3(0,0,focalLength) - viewportU/2 - viewportV/2;
    auto pixel100 = viewportUL + 0.5* (pixelDeltaU + pixelDeltaV);

    // Crianndo o Backgound
    std::cout << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

    for (int j = 0; j < imgHeight; ++j) { // For por todas as linhas
        for (int i = 0; i < imgWidth; ++i) { // For por todas as colunas
            // Calculamos o centro do Pixel a partir do pixel inicial + a posicao dele x o delta de cada posicao
            auto pixelCenter = pixel100 + (i * pixelDeltaU) + (j * pixelDeltaV); 
            auto rayDirection = pixelCenter - cameraCenter; // Definimos a direcao do Raio como a diferenca do pixel central com a central da camera
            Ray r(cameraCenter, rayDirection); // Tracamos o raio a partir do centro da camera e da direcao do Raio
            color3 pixelColor = rayColor(r); // Definimos a cor do pixel
            write_color(std::cout, pixelColor); // Imprimos as cores do pixel
        }
    }
}
