#ifndef JAMPI_OVERLOADTAG_H
#define JAMPI_OVERLOADTAG_H

namespace jampi {
// Tag para especializar um tipo de decidir entre uma implementacao (geral) ou outra
// (void, especifico).
    template<class T>
    class OverloadTag {
        typedef T type;
    };
}

#endif //JAMPI_OVERLOADTAG_H
