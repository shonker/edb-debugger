/*
Copyright (C) 2006 - 2015 Evan Teran
                          evan.teran@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PE32_20070718_H_
#define PE32_20070718_H_

#include "IBinary.h"
#include "pe_binary.h"

namespace BinaryInfoPlugin {

class PEBinaryException : public std::exception {
	public:
	enum reasonEnum {
		INVALID_ARGUMENTS = 1,
		READ_FAILURE = 2,
		INVALID_PE = 3,
		INVALID_ARCHITECTURE = 4
	};
        explicit PEBinaryException(reasonEnum reason);

		const char * what() const noexcept override;

	private:
		reasonEnum reason_;
};

class PE32 : public IBinary {
public:
    explicit PE32(const std::shared_ptr<IRegion> &region);
    ~PE32() override = default;

public:
    bool native() const override;
    edb::address_t calculate_main() override;
    edb::address_t debug_pointer() override;
    edb::address_t entry_point() override;
    size_t header_size() const override;
    const void *header() const override;
    QVector<Header> headers() const override;
    edb::address_t base_address() const override;

private:
	std::shared_ptr<IRegion> region_;
	IMAGE_DOS_HEADER dos_;
	IMAGE_NT_HEADERS32 pe_;
};

}

#endif
