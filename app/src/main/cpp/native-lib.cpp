#include <jni.h>
#include <string>
#include "AStar.hpp"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_kinglloy_astar_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_kinglloy_astar_MainActivity_getPath(JNIEnv *env, jobject instance) {

    AStar::Generator generator;
    generator.setWorldSize({7, 7});
    generator.addCollision({1, 3});
    generator.addCollision({2, 3});
    generator.addCollision({3, 3});
    generator.addCollision({4, 3});
    generator.addCollision({5, 3});
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);

    auto path = generator.findPath({3, 1}, {3, 5});

    jclass cls_ArrayList = env->FindClass("java/util/ArrayList");
    jmethodID construct = env->GetMethodID(cls_ArrayList, "<init>", "()V");
    jobject obj_ArrayList = env->NewObject(cls_ArrayList, construct, "");
    jmethodID arrayList_add = env->GetMethodID(cls_ArrayList, "add", "(Ljava/lang/Object;)Z");

    jclass cls_pair = env->FindClass("com/kinglloy/astar/Point");
    jmethodID construct_pair = env->GetMethodID(cls_pair, "<init>", "(II)V");

    for (auto &coordinate : path) {
        jobject obj_pair = env->NewObject(cls_pair, construct_pair, coordinate.x, coordinate.y);
        env->CallBooleanMethod(obj_ArrayList, arrayList_add, obj_pair);
    }
    return obj_ArrayList;
}