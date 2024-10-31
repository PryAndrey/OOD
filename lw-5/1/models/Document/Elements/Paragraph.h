#pragma once

#include <utility>
#include "IParagraph.h"

class Paragraph: public IParagraph {
public:
    explicit Paragraph(std::string text): m_text(std::move(text)) {}

    [[nodiscard]] std::string GetText() const override;
    void SetText(const std::string& text) override;

private:
    std::string m_text;
};
