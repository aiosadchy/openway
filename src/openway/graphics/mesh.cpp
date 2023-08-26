#include "openway/graphics/mesh.hpp"

#include <stdexcept>
#include <vector>

#include <tiny_obj_loader.h>

#include "openway/utility/log.hpp"

Mesh::Mesh(const std::string &obj_file) {
    tinyobj::attrib_t attributes{};
    std::vector<tinyobj::shape_t> shapes{};
    std::vector<tinyobj::material_t> materials{};
    std::string warnings{};
    std::string errors{};
    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &materials,
        &warnings,
        &errors,
        obj_file.c_str()
    );
    if (!errors.empty()) {
        OW_LOG_ERROR("tinyobjloader: file \"", obj_file, "\":", errors);
    }
    if (!warnings.empty()) {
        OW_LOG_WARNING("tinyobjloader: file \"", obj_file, "\":", warnings);
    }
    if (!success) {
        OW_LOG_THROW std::runtime_error{
            "failed to load mesh form \"" + obj_file + "\"",
        };
    }
}

void Mesh::draw() const {
}
