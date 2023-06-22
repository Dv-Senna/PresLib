#pragma once


#define PL_CLASS_NO_COPY(className) className(const className &) = delete; const className &operator=(const className &) = delete

#define PL_CLASS_NO_MOVE(className) className(className &&) noexcept = delete; const className &operator=(className &&) = delete

#define PL_CLASS_NO_COPY_MOVE(className) PL_CLASS_NO_COPY(className); PL_CLASS_NO_MOVE(className)