#ifndef __ABSTRACT_FACTORY_DP_H__
#define __ABSTRACT_FACTORY_DP_H__

class Product1 {
    public :
        void execFeature1() = 0;
        void execFeature2() = 0;
};

class Product1Context {
    public :
        void setAttr1() = 0;
        void setAttr2() = 0;
    
};

class Product1Impl1 {
    public :
        void execFeature1() {}
        void execFeature2() {}
};

class ProductContext1Impl1 {
    public :
        void setAttr1();
        void setAttr2();
};

class Product1Impl2 {
};

class ProductContext1Impl2 {
};

class Product2 {

};

class Product2Context {

};

class Product2Impl1 {

};

class ProductContext2Impl1 {
};

class Product2Impl2 {
};

class ProductContext2Impl2 {
};

class ProductSuiteAbstractFactory() {
    pubic :
        Product1& createProduct1(const Product1Context& ctxt) = 0;
        Product2& createProduct2(const Product2Context& ctxt) = 0;
};

class ProductSuiteFactoryImpl1 : public ProductSuiteAbstractFactory {
    public : 
        Product1& createProduct1(const Product1Context& ctxt) {
        }
        
        Product2& createProduct2(const Product2Context& ctxt) {
        }
};

class ProductSuiteFactoryImpl2 : public ProductSuiteAbstractFactory {
    public : 
        Product1& createProduct1(const Product1Context& ctxt) {
        }
        
        Product2& createProduct2(const Product2Context& ctxt) {
        }
};

#endif /* __ABSTRACT_FACTORY_DP_H__ */
