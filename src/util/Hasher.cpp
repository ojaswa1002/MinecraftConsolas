#include "Hasher.h"

#include <type_traits>
#include <utility>

#include "util/console/StringHelpers.h"

Hasher::Hasher(std::wstring& salt) { this->salt = salt; }

std::wstring Hasher::getHash(std::wstring& name) {
    // 4J Stu - Removed try/catch
    // try {
    std::wstring s = std::wstring(salt).append(name);
    // MessageDigest m;
    // m = MessageDigest.getInstance("MD5");
    // m.update(s.getBytes(), 0, s.length());
    // return new BigInteger(1, m.digest()).toString(16);

    // TODO 4J Stu - Will this hash us with the same distribution as the MD5?
    return _toString(std::hash<std::wstring>{}(s));
    //}
    // catch (NoSuchAlgorithmException e)
    //{
    //	throw new RuntimeException(e);
    //}
}
