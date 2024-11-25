# **Interactive BVH Visualization Application**

## **Overview**
This project is a **prototype interactive application** designed to visualize and manipulate **Bounding Volume Hierarchies (BVH)**. It allows users to navigate scenes, manipulate 3D objects, and observe the BVH construction process at various depth levels. 

---

## **Main Features**
- **Interactive BVH Visualization**: Real-time exploration of the BVH at various depth levels.
- **3D Object Manipulation**: Translate, rotate, and scale objects directly in the scene.
- **Dynamic Scene Navigation**: Use a PinHole camera for smooth navigation.
- **BVH Construction**: Implements the **Median Cut** method for hierarchy generation.
- **Realistic Rendering**: Supports the **Blinn-Phong illumination model** .
- **Graphical Interface**: Built with Dear ImGui .

---

## **External Dependencies**
The following libraries and tools are required to run the application:
- **GLEW**
- **GLFW3**
- **CMake**

---
## **Usage**

### **Controls**
#### **Camera Navigation**
- **`W`**: Move forward.
- **`S`**: Move backward.
- **`A`**: Move left.
- **`D`**: Move right.
- **`Space`**: Move up.
- **`Ctrl`**: Move down.
- **`F`**: Toggle camera lock/unlock.

#### **GUI Features**
Access various features through the graphical user interface:
- **BVH Visualization**:
  - Enable or disable BVH rendering.
  - Adjust BVH depth levels using a slider.
  - Toggle rendering modes (Wireframe, Blinn-Phong).
- **Object Rendering**:
  - Enable or disable object visualization.
  - Render object wireframes or normals.
- **Wireframe Settings**:
  - Adjust the wireframe thickness for both BVH and object rendering.
- **Lighting**:
  - Customize Blinn-Phong lighting parameters, such as ambient, diffuse, specular, and exponent values.

### **Running the Application**
Run the application with the following command:
```bash
./BVHViwer <model_name> # for instance (./BVHViwer ../models/horse.ply)

```

### **Features**
- Navigate the scene using the camera controls.
- Load 3D models in **OBJ** or **PLY** formats.
- Visualize BVH construction for loaded models.
- Adjust the depth of the BVH visualization.
- Manipulate objects via translation, rotation, and scaling.
- Observe lighting effects with Blinn-Phong shading.

---

## **Installation**
- **Prerequisites**
1. Install a C++ compiler (e.g., GCC, Clang, MSVC).
2. Install **CMake** (minimum version 3.15 recommended).
3. Ensure  GLFW3 and GLEW.

### **Steps**
1. Clone the repository:
   ```bash
   git clone https://github.com/Matz-Mp4/BVH-Viewer
   cd BVH-Viewer
   ```
2. Build the project:
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

