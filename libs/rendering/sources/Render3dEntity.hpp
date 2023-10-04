// /*! \class Render3dEntity
//  *  \brief Brief class description
//  *
//  *  Detailed description
//  */

// #include "raylib.h"

// #include <string>
// #include <optional>

// #include "IRenderEntity.hpp"

// #define SCREEN_WIDTH    800
// #define SCREEN_HEIGHT   450

// class Render3dEntity : public IRenderEntity {

// public:
//     Render3dEntity(std::string object_path, std::string asset_path);
//     virtual ~Render3dEntity();

//     void drawEntity();

//     void setPos(std::optional<float> pos_x, std::optional<float> pos_y, std::optional<float> pos_z);
//     void setScale(float scale);

//     Model getModel();
//     void setRotationAxis(std::optional<float> pos_x, std::optional<float> pos_y, std::optional<float> pos_z);

// private:
//     Model _model;
//     Texture2D _texture;
//     // Vector3 _pos;
//     // float _rotation;
//     // float _scale;
//     // Color _tint;
//     // Vector3 _rotationAxis = {0.0f, 0.0f, 0.0f};
// };
