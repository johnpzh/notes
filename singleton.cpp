class Singleton {
private:
    Singleton() {}
    static Singleton *object_;
    
public:
    Singleton(const Singleton &) = delete;
    void operator=(const Singleton &) = delete;
    
    static Singleton *get_instance();
};

Singleton *Singleton::object_ = nullptr;

Singleton *Singleton::get_instance() {
    if (!object_) {
        object_ = new Singleton();
    }
    
    return object_;
}
