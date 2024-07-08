#pragma once

namespace std
{
	namespace filesystem
	{
		class path;
	}
}

struct _TTF_Font;

class Font final
{
public:
	
	explicit Font(const std::filesystem::path& path, unsigned int size);
	~Font();

	Font(const Font&) = delete;
	Font(Font&&) = delete;
	Font& operator= (const Font&) = delete;
	Font& operator= (const Font&&) = delete;

	_TTF_Font* GetFont() const;
	
private:

	_TTF_Font * const m_Font;
};