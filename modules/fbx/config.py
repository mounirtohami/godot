def can_build(env, platform):
    if env["disable_3d"]:
        return False
    env.module_add_dependencies("fbx", ["gltf"])


def configure(env):
    pass


def get_doc_classes():
    return [
        "EditorSceneFormatImporterFBX2GLTF",
        "EditorSceneFormatImporterUFBX",
        "FBXDocument",
        "FBXState",
    ]


def get_doc_path():
    return "doc_classes"
