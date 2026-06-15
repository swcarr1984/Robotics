/* Created 12/6/26 S.Carr
   2-Axis, 3-Joint reverse-kinematics with simple CCD (Cyclic Coordinate Descent) solver
*/

#include <cmath>
#include <iostream>
#include <array>
#include <algorithm>

struct Vec2 {
    double x{};
    double y{};
};

struct Link {
    double length{};
};

struct Arm {
    std::array<Link, 3> links;
    std::array<double, 3> angles; // radians: [theta0, theta1, theta2]
};



// Forward kinematics: compute joint positions (including end effector)
void forwardKinematics(const Arm& arm, std::array<Vec2, 4>& joints) {
    double angleSum = 0.0;
    joints[0] = {0.0, 0.0}; // base at origin

    for (size_t i = 0; i < arm.links.size(); ++i) {
        angleSum += arm.angles[i];
        joints[i + 1].x = joints[i].x + arm.links[i].length * std::cos(angleSum);
        joints[i + 1].y = joints[i].y + arm.links[i].length * std::sin(angleSum);
    }
}

// CCD step: adjust one joint to bring end effector closer to target
void ccdStep(Arm& arm, const Vec2& target) {
    std::array<Vec2, 4> joints;
    forwardKinematics(arm, joints);

    // iterate joints from end toward base
    for (int i = 2; i >= 0; --i) {
        Vec2 jointPos = joints[i];
        Vec2 endPos   = joints[3];

        // vector from joint to end effector
        Vec2 r1{endPos.x - jointPos.x, endPos.y - jointPos.y};
        // vector from joint to target
        Vec2 r2{target.x - jointPos.x, target.y - jointPos.y};

        double len1 = std::hypot(r1.x, r1.y);
        double len2 = std::hypot(r2.x, r2.y);
        if (len1 < 1e-9 || len2 < 1e-9) continue;

        // normalize
        r1.x /= len1; r1.y /= len1;
        r2.x /= len2; r2.y /= len2;

        std::cout << __cplusplus << "\n";

        // angle between r1 and r2
        double dot = r1.x * r2.x + r1.y * r2.y;
        dot = std::clamp(dot, -1.0, 1.0);
        double cross = r1.x * r2.y - r1.y * r2.x; // sign of rotation
        double delta = std::acos(dot);
        if (cross < 0) delta = -delta;

        arm.angles[i] += delta;

        // recompute FK after changing this joint
        forwardKinematics(arm, joints);
    }
}

int main() {
    Arm arm{
        /* links  */ {{{1.0}, {1.0}, {0.5}}},
        /* angles */ {{0.0, 0.0, 0.0}}
    };

    Vec2 target{1.5, 0.5};

    for (int iter = 0; iter < 200; ++iter) {
        ccdStep(arm, target);

        std::array<Vec2, 4> joints;
        forwardKinematics(arm, joints);
        Vec2 end = joints[3];

        double err = std::hypot(end.x - target.x, end.y - target.y);
        std::cout << "iter " << iter
                  << "  end=(" << end.x << ", " << end.y << ")"
                  << "  err=" << err << "\n";

        if (err < 1e-3) break;
    }

    std::cout << "\nFinal joint angles (rad):\n";
    for (size_t i = 0; i < arm.angles.size(); ++i) {
        std::cout << "theta" << i << " = " << arm.angles[i] << "\n";
    }
}