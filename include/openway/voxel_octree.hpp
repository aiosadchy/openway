#ifndef OPENWAY_VOXEL_OCTREE_HPP
#define OPENWAY_VOXEL_OCTREE_HPP

#include <cstdint>
#include <limits>

#include "openway/common.hpp"


enum class Voxel : int {
    Empty = 0,
    Full  = 1,
};


class Leaf {
public:
    // TODO: create bitset and use it as a base class
    using Data = std::uint64_t;

    class Proxy {
    public:
        Proxy(Leaf &leaf, Index x, Index y, Index z)
            : m_leaf(&leaf)
            , m_x(x)
            , m_y(y)
            , m_z(z) {
        }

        operator Voxel() const {
            return m_leaf->get(m_x, m_y, m_z);
        }

        Proxy& operator=(Voxel value) {
            m_leaf->set(m_x, m_y, m_z, value);
            return *this;
        }

    private:
        Leaf *m_leaf;
        Index m_x;
        Index m_y;
        Index m_z;

    };

    explicit Leaf(Voxel default_value = Voxel::Empty)
        : m_data(
            (default_value == Voxel::Empty)
            ? Data{0}
            : std::numeric_limits<Data>::max()
        ) {
    }

    explicit Leaf(Data data)
        : m_data(data) {
    }

    [[nodiscard]] Voxel get(Index x, Index y, Index z) const {
        Data bit = (((x << 2) + y) << 2) + z;
        return ((m_data & (Data{1} << bit)) == 0)
               ? Voxel::Empty
               : Voxel::Full;
    }

    void set(Index x, Index y, Index z, Voxel value) {
        Data bit = (((x << 2) + y) << 2) + z;
        Data new_value = (value == Voxel::Empty) ? 0 : 1;
        m_data = (m_data & ~(Data{1} << bit)) | (new_value << bit);
    }

    [[nodiscard]] Voxel operator()(Index x, Index y, Index z) const {
        return get(x, y, z);
    }

    [[nodiscard]] Proxy operator()(Index x, Index y, Index z) {
        return Proxy{*this, x, y, z};
    }

    [[nodiscard]] Data data() const {
        return m_data;
    }

private:
    Data m_data;

};


class VoxelOctree {
public:
    struct Aggregate {
        std::uint8_t node_values;
        std::uint8_t child_nodes;
        std::uint32_t first_child_index;
    };

    union Node {
        Aggregate aggregate;
        Leaf leaf;
    };

private:

};


#endif // OPENWAY_VOXEL_OCTREE_HPP
