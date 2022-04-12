#include <string>
#include <cstdlib>

#include "Camera.h"
#include "Constants.h"
#include "Graphics.h"
#include "Mesh.h"

// Global variables
Camera camera;
bool debug = false;
bool running = false;
bool paused = false;

struct GameObject {
    Mesh* mesh;
    Color color;

    Vec3 position;
    Vec3 rotation;
    Vec3 scale;

    struct triangle {
        Vec2 points[3];
        Color color;
    };

    std::vector<triangle> projected_triangles;
} cube;

void Init(int width, int height, const std::string& obj_file) {
    running = Graphics::OpenWindow(width, height);

    // Loading the mesh
    cube.mesh = new Mesh();
    cube.mesh->LoadObjFileData(obj_file);
    cube.color = Color::White();
    cube.position = Vec3(0, 0, 4);
    cube.rotation = Vec3(0, 0, 0);
    cube.scale = Vec3(1, 1, 1);

    // Camera initialization
    camera.position = Vec3(0, 0, -5);
    camera.target = Vec3(0, 0, 0);
    camera.light_direction = Vec3(0, 0, 1);
    camera.zoom = 1.0f;
    float fov = PI / 3.0;
    float aspect = (float)height / (float)width;
    float znear = 0.1;
    float zfar = 100.0;
    camera.projection_matrix = Mat4::CreatePerspective(fov, aspect, znear, zfar);
}

void Destroy() {
    Graphics::CloseWindow();
}

void Update(float dt) {
    // Clear previous projections
    cube.projected_triangles.clear();

    // Update body & camera
    cube.rotation += Vec3(0, dt, 0);
    camera.position += Vec3(0, dt, 0);

    // Create world matrix
    Mat4 scale_matrix = Mat4::CreateScale(cube.scale.x, cube.scale.y, cube.scale.z);
    Mat4 rotation_matrix = Mat4::CreateRotationXYZ(cube.rotation.x, cube.rotation.y, cube.rotation.z);
    Mat4 translate_matrix = Mat4::CreateTranslate(cube.position.x, cube.position.y, cube.position.z);
    Mat4 view_matrix = Mat4::CreateLookAt(camera.position, camera.target, Vec3(0,1,0));
    Mat4 world_matrix = view_matrix * translate_matrix * rotation_matrix * scale_matrix;

    // Iterate through mesh faces
    for(int i = 0, max = cube.mesh->GetNumberOfFaces(); i < max; i++) {
        // Get the face with vertices
        std::vector<Vec3> face_vertices = cube.mesh->GetFaceVertices(i);

        // World Space: apply world matrix transform to each vertex of the face
        std::vector<Vec4> world_face_vertices;
        for(int j = 0; j < 3; j++) {
            world_face_vertices.push_back(Vec4(world_matrix * face_vertices[j].TransformIntoVec4()));
        }

        /**********************************
         * Back-face culling algorithm
         **********************************/
        // Find vectors B-A and C-A in the triangle
        Vec3 vertex_a = world_face_vertices[0].TransformIntoVec3();
        Vec3 vertex_b = world_face_vertices[1].TransformIntoVec3();
        Vec3 vertex_c = world_face_vertices[2].TransformIntoVec3();
        Vec3 vector_ab = (vertex_b - vertex_a).Normalize();
        Vec3 vector_ac = (vertex_c - vertex_a).Normalize();

        // Compute face normal through cross product
        Vec3 face_normal = vector_ab.Cross(vector_ac).Normalize();

        // Find the vector between vertex A in the triangle and the camera origin
        // and calculate how aligned the camera ray is with the face normal
        Vec3 camera_ray = camera.position - vertex_a;
        float dot_normal_camera = face_normal.Dot(camera_ray);

        // Force the next iteration of the loop and skip adding it to the list of
        // vertices to project if the triangle is looking away from the camera
        if (dot_normal_camera < 0 ) {
            continue;
        }

        // Loog through vertices of the face
        std::vector<Vec4 *> projected_vertices;
        for(auto world_face_vertex:world_face_vertices) {
            // Project current vertex
            Vec4 *projected_vertex = new Vec4(camera.projection_matrix * world_face_vertex);

            // Perform perspective divide with original z-value that is now stored in w
            if (projected_vertex->w != 0.0) {
                projected_vertex->x /= projected_vertex->w;
                projected_vertex->y /= projected_vertex->w;
                projected_vertex->z /= projected_vertex->w;
            }

            // Flip vertically since the y values of the 3D mesh grow bottom->up and in screen space y values grow top->down
            projected_vertex->y *= -1;

            // Scale the projected points into the view
            projected_vertex->x *= Graphics::Width() / 2.0;
            projected_vertex->y *= Graphics::Height() / 2.0;

            // Translate the projected points to the middle of the screen
            projected_vertex->x += (Graphics::Width() / 2.0);
            projected_vertex->y += (Graphics::Height() / 2.0);

            // Save the projected vertex for this face
            projected_vertices.push_back(projected_vertex);
        }

        // Calculate lighting
        float light_intentsity_factor = -face_normal.Dot(camera.light_direction);
        Color face_color = Color::White().Darkened(light_intentsity_factor);

        // Create the final projected triangle that will be rendered in screen space
        cube.projected_triangles.push_back({
            Vec2(projected_vertices[0]->x, projected_vertices[0]->y),
            Vec2(projected_vertices[1]->x, projected_vertices[1]->y),
            Vec2(projected_vertices[2]->x, projected_vertices[2]->y),
            face_color
        });
    }
}

void Render(float dt) {
    Graphics::DrawGrid();

    for (auto triangle: cube.projected_triangles) {
        Graphics::DrawFillTriangle(
            triangle.points[0].x,
            triangle.points[0].y,
            triangle.points[1].x,
            triangle.points[1].y,
            triangle.points[2].x,
            triangle.points[2].y,
            triangle.color
        );
    }

    Graphics::RenderFrame();
}

void Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                if (event.key.keysym.sym == SDLK_p)
                    paused = !paused;
        }
    }
}

float Wait() {
    // Wait some time until the reach the target frame time in milliseconds
    static int timePreviousFrame;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0)
        SDL_Delay(timeToWait);

    // Calculate the deltatime in seconds
    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
    if (deltaTime > 0.016)
        deltaTime = 0.016;

    // Set the time of the current frame to be used in the next one
    timePreviousFrame = SDL_GetTicks();

    return deltaTime;
}

int main(int argc, char *argv[]) {

    if (argc == 4) {
        Init(atoi(argv[1]), atoi(argv[2]), argv[3]);

        while (running) {
            Input();

            float dt = Wait();

            Update(dt);

            Render(dt);
        }

        Destroy();

    } else {
        std::cerr << "\nUsage: " << argv[0] << " WINDOW_WIDTH WINDOW_HEIGHT PATH_TO_OBJ_FILE\n";
        std::cerr << "\nExample: " << argv[0] << " 800 600 cube.obj\n\n";
    }

    return 0;
}
