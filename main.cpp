#include "tracer.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "bezier.h"
#include "revolution.h"
#include "matrix.h"

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>


int main(int argc, char* argv[])
{
    int w = 640, h = 480;
    Scene scene;

    if (argc != 3)
    {
        std::cout << "graphics <scene> <frame>\n";
        return 1;
    }

    int n = atoi(argv[1]);
    int frame_num = atoi(argv[2]);

    double t = frame_num / 30.0;

    std::ostringstream filename;
    filename << "frames/" << n << std::setw(4) << std::setfill('0') << frame_num << ".ppm";

    ImageWriter image(w, h, filename.str().c_str());

    if (!n)
    {
    Vec2 king_points[] = {
        Vec2(0,-13.826785), Vec2(-1.2440054,-13.831371), Vec2(0.10667656,-12.287839),
        Vec2(-0.51516043,-11.915636), Vec2(-1.1739324,-11.521326), Vec2(-2.1404574,-11.565574),
        Vec2(-2.2984044,-11.304584), Vec2(-2.4563524,-11.043594), Vec2(-1.5721924,-9.4037618),
        Vec2(-1.5388044,-8.936604), Vec2(-1.5054154,-8.4694457), Vec2(-1.4554754,-8.1048616),
        Vec2(-1.6818644,-8.0700587), Vec2(-2.1353864,-8.0003387), Vec2(-1.8161134,-7.5758075),
        Vec2(-2.0156724,-7.5792228), Vec2(-2.3719194,-7.5853199), Vec2(-2.7671264,-7.5273963),
        Vec2(-2.7194054,-7.150041), Vec2(-2.6716844,-6.7726857), Vec2(-1.6062714,-7.1026055),
        Vec2(-1.5946724,-6.7430081), Vec2(-1.4912014,-3.5352037), Vec2(-1.6557664,0.54747486),
        Vec2(-2.3436954,0.75201286), Vec2(-2.8033804,0.88868786), Vec2(-2.7008154,1.1005038),
        Vec2(-2.7478354,1.2654938), Vec2(-2.9407244,1.9423128), Vec2(-3.6507534,2.0861628),
        Vec2(-3.9510814,2.5978338), Vec2(-4.0799354,2.8173618), Vec2(-4.0657044,3.0983618),
        Vec2(-3.9848014,3.3410708), Vec2(-3.9067484,3.5752308), Vec2(-3.4886904,3.6740958),
        Vec2(-3.5922324,3.9609998), Vec2(-3.6994644,4.2581318), Vec2(-4.1123624,4.2540118),
        Vec2(-4.2988574,4.4715888), Vec2(-4.3984844,4.5878198), Vec2(-4.4737094,4.9963788),
        Vec2(-4.2988574,4.9961438), Vec2(-2.8616664,4.9942158), Vec2(-0.46608043,4.9857958),
        Vec2(0,4.9903588)
    };

    Vec2 pawn_points[] = {
        Vec2(0, 0.0013893285), Vec2(-0.18194219,-0.0016027034), Vec2(-0.39309925,0.11633676),
        Vec2(-0.48897346,0.31269775 ), Vec2(-0.58300641,0.50528763), Vec2(-0.54361761,0.76152864),
        Vec2(-0.47116611,0.86857738), Vec2(-0.36411915,1.0267417), Vec2(-0.3591511,1.0236918),
        Vec2(-0.17982504,1.1272353), Vec2(-0.034209838, 1.2095904), Vec2(-0.60230158, 1.2578403),
        Vec2(-0.5591118, 1.3877637), Vec2(-0.52185491, 1.4998401), Vec2(-0.35264315, 1.4717721),
        Vec2(-0.31164292, 1.4994635), Vec2(-0.24834655, 1.5422136), Vec2(-0.32492484, 2.6355541),
        Vec2(-0.48632683, 2.7002372), Vec2(-0.56809851, 2.733008), Vec2(-0.55360559, 2.8503029),
        Vec2(-0.58822581, 2.8677869), Vec2(-0.69275175, 2.9205751), Vec2(-0.8211972, 3.0006106),
        Vec2(-0.83569484, 3.12842), Vec2(-0.85563284, 3.3041912), Vec2(-0.7809794,3.2803101),
        Vec2(-0.77721529,3.3632081), Vec2(-0.77465109,3.4196804), Vec2(-0.77465109,3.4196804),
        Vec2(-0.77465109,3.4196804), Vec2(-0.90914127,3.5223423), Vec2(-0.90914127,3.5223423),
        Vec2(-0.89392271,3.6124529), Vec2(-0.88212385,3.6238776), Vec2(-0.088211651,3.6130572),
        Vec2(0, 3.6)
    };


    Material black_chess;
    black_chess.diffuse = Vec3(0.1, 0.1, 0.1);
    black_chess.ambient = Vec3(0.1, 0.1, 0.1);
    black_chess.specular = Vec3(0.9, 0.9, 0.9);
    black_chess.shininess = 2.0;

    Material white_chess;
    white_chess.diffuse = Vec3(1, 0.78, 0.3);
    white_chess.ambient = Vec3(0.1, 0.1, 0.1);
    white_chess.specular = Vec3(0.9, 0.9, 0.9);
    white_chess.shininess = 2.0;


    Checkerboard checkers;

    Material mirror_2;
    mirror_2.diffuse = Vec3(0.8, 0.8, 0.8);
    mirror_2.mirror = Vec3(0.2, 0.2, 0.2);
    
    Plane plane;
    plane.set_texture(&checkers);
    plane.set_material(mirror_2);


    SphereLight light(Vec3(3, -3 , 5), 0.8, Vec3(1, 1, 1)*20.0);
    //PointLight light(Vec3(3, -3 , 5), Vec3(1, 1, 1)*20.0);
    PointLight light_2(Vec3(-8, 2 , 7), Vec3(1, 1, 1)*20.0);
    //SphereLight light(Vec3(3, -3 , 1), 0.5, Vec3(1, 1, 1)*15.0);
    //SphereLight light(Vec3(0, -0.5 , 1), 0.5, Vec3(1, 1, 1)*15.0);

    Bezier king_bezier(king_points, 15, 0.0001);
    Revolution king(king_bezier);
    king.transform( Transform::translate(Vec3(0, 0, -5)));
    king.transform(Transform::scale(Vec3(1.0, 1.0, -1.0) / 9.0));
    king.transform( Transform::translate(Vec3(0.5, -0.5, 0)));
    king.set_material(black_chess);


    Bezier pawn_bezier(pawn_points, 12, 0.00001);
    Revolution pawn_1(pawn_bezier), pawn_2(pawn_bezier);

    pawn_1.transform( Transform::translate(Vec3(0, 0, -3.6)));
    pawn_1.transform(Transform::scale(Vec3(1.0, 1.0, -1.0)/ 2.5));
    pawn_1.transform( Transform::translate(Vec3(-0.5, 0.5, 0)));
    pawn_1.set_material(black_chess);

    pawn_2.transform( Transform::translate(Vec3(0, 0, -3.6)));
    pawn_2.transform(Transform::scale(Vec3(1.0, 1.0, -1.0)/ 2.5));
    pawn_2.transform( Transform::translate(Vec3(-0.5, -1.5, 0)));
    pawn_2.set_material(white_chess);


    scene.add(&king);
    scene.add(&pawn_2);
    scene.add(&pawn_1);

    scene.add(&plane);
    scene.add_light(&light);
    scene.add_light(&light_2);
    scene.set_ambient(0.0*Vec3(0.3, 0.3, 0.3));


    double phi = t / 10.0 * (2.0 * M_PI);
    double r = 6.0;

    Vec3 cam_pos(r*cos(phi), r*sin(phi), 2.3);
    Vec3 cam_dir(-cos(phi), -sin(phi), -0.3);
    cam_dir /= cam_dir.length();

    Camera camera(cam_pos, cam_dir, double(w)/h, M_PI/4, Vec3(0, 0, 1));

    Tracer tracer(scene);
    tracer.trace(camera, image);
    }
    else //scene 2 - spheres
    {
        Material mirror;
        mirror.diffuse = Vec3(0.1, 0, 0.4);
        mirror.mirror = Vec3(0.7, 0.7, 0.7);
        mirror.shininess = 2.0;

        Material blue;
        blue.diffuse = Vec3(0.13, 0, 0.4);

        Material purple;
        purple.diffuse = Vec3(210, 26, 126)/255;
        purple.shininess = 2.0;
        purple.specular = Vec3(0.5, 0.5, 0.5);

        Material pink;
        pink.specular = Vec3(0.7, 0.7, 0.7);
        pink.shininess = 2.0;

        Checkerboard_round checkers;
        Marble marble;

        Sphere sphere;
        sphere.set_material(pink);

        double phi = t / 6.0 * (2.0 * M_PI);
        double r = 0.5 + 5/sqrt(sqrt(30*t));

        Vec3 dir(-cos(phi), -sin(phi), 0);
        dir /= dir.length();
        
        double beta;
        if (phi < M_PI/2)
            beta = acos(dot(dir, Vec3(1, 0, 0)));
        else
            beta = -acos(dot(dir, Vec3(1, 0, 0)));
        
        Mat3 linear;
        linear =  Mat3::rotate_z(beta)  *  Mat3::rotate_x(-phi*r);
        Transform tr(Vec3(), linear);

        sphere.transform(Transform::translate(Vec3(r*cos(phi), r*sin(phi), 1))*tr);
        marble.transform(sphere.get_transform());
        sphere.set_texture(&marble);
        Sphere sphere1;
        sphere1.set_material(mirror);

        
        double phi1 = t / 6.0 * (2.0 * M_PI)  - M_PI;

        Vec3 dir1(-cos(phi1), -sin(phi1), 0);
        dir1 /= dir1.length();
        
        double beta1 = acos(dot(dir1, Vec3(1, 0, 0)));
        
        Mat3 linear1;
        linear1 =  Mat3::rotate_z(beta1)  *  Mat3::rotate_x(-phi1*r);
        Transform tr1(Vec3(), linear1);

        sphere1.transform(Transform::translate(Vec3(r*cos(phi1), r*sin(phi1), 1))*tr1);

        Plane plane;
        plane.set_material(purple);
        plane.set_texture(&checkers);

        scene.add(&sphere);
        scene.add(&sphere1);
        scene.add(&plane);

        //PointLight light(Vec3(-2, -2 , 10), Vec3(1, 1, 1)*50.0);
        SphereLight light(Vec3(-2, -2 , 10), 0.6, Vec3(1, 1, 1)*50.0);
        scene.add_light(&light);

        Vec3 camera_dir = Vec3(0, 30, -10);
        camera_dir = camera_dir/camera_dir.length();
        Camera camera(Vec3(0, -12, 5), camera_dir, double(w)/h, M_PI/4, Vec3(0, 0, 1));

        Tracer tracer(scene);
        tracer.trace(camera, image);
    }

    

    return 0;
}
