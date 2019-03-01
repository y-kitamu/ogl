#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>


bool loadOBJ(std::string path, std::vector<glm::vec3> &out_vertices,
             std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals) {
    std::vector<std::vector<int> > vert_idx, uv_idx, norm_idx;
    std::vector<glm::vec3> tmp_vert, tmp_norm;
    std::vector<glm::vec2> tmp_uv;

    std::ifstream ifs(path.c_str());

    if (!ifs.is_open()) {
        std::cout << "Can not open file" << std::endl;
        return false;
    }

    while (!ifs.eof()) {
        std::string str, line_head;
        std::getline(ifs, str);

        std::stringstream ss(str);
        ss >> line_head;

        if (line_head == "v") {
            glm::vec3 vert;
            ss >> vert.x >> vert.y >> vert.z;
            tmp_vert.push_back(vert);
            std::cout << vert.x << ", " << vert.y << ", " << vert.z << std::endl;
        } else if (line_head == "vt") {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            tmp_uv.push_back(uv);
        } else if (line_head == "vn") {
            glm::vec3 norm;
            ss >> norm.x >> norm.y >> norm.z;
            tmp_norm.push_back(norm);
        } else if (line_head == "f") {
            std::vector<int> vert(3), uv(3), norm(3);
            char c_tmp;
            std::sscanf(ss.str().c_str(), "%c %d/%d/%d %d/%d/%d %d/%d/%d",
                        &c_tmp, &vert[0], &uv[0], &norm[0], &vert[1], &uv[1], &norm[1], &vert[2], &uv[2], &norm[2]);
            vert_idx.push_back(vert);
            uv_idx.push_back(uv);
            norm_idx.push_back(norm);
        }
    }

    for (int i = 0; i < vert_idx.size(); i++) {
        for (int j = 0; j < 3; j++) {
            // std::cout << "(" << tmp_vert[vert_idx[i][j]].x << ", " << tmp_vert[vert_idx[i][j]].y << ", " << tmp_vert[vert_idx[i][j]].z
            //           << "), (" << tmp_uv[uv_idx[i][j]].x  << ", " << tmp_uv[uv_idx[i][j]].x << ")" << std::endl;
            out_vertices.push_back(tmp_vert[vert_idx[i][j] - 1]);
            out_uvs.push_back(tmp_uv[uv_idx[i][j] - 1]);
            out_normals.push_back(tmp_norm[norm_idx[i][j] - 1]);
        }
    }
}
