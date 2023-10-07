#pragma once


#define PL_CLASS_NO_COPY(className) className(const className &) = delete; const className &operator=(const className &) = delete
#define PL_CLASS_NO_MOVE(className) className(className &&) noexcept = delete; const className &operator=(className &&) = delete
#define PL_CLASS_NO_COPY_MOVE(className) PL_CLASS_NO_COPY(className); PL_CLASS_NO_MOVE(className)

#define PL_TEMPLATE_CLASS_NO_COPY(className, ...) className(const className<__VA_ARGS__> &) = delete; const className<__VA_ARGS__> &operator=(const className<__VA_ARGS__> &) = delete
#define PL_TEMPLATE_CLASS_NO_MOVE(className, ...) className(className<__VA_ARGS__> &&) noexcept = delete; const className<__VA_ARGS__> &operator=(className<__VA_ARGS__> &&) = delete
#define PL_TEMPLATE_CLASS_NO_COPY_MOVE(className, ...) PL_TEMPLATE_CLASS_NO_COPY(className, __VA_ARGS__); PL_TEMPLATE_CLASS_NO_MOVE(className, __VA_ARGS__)