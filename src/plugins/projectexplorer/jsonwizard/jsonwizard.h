/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://www.qt.io/licensing.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef JSONWIZARD_H
#define JSONWIZARD_H

#include "../projectexplorer_export.h"

#include <coreplugin/generatedfile.h>

#include <utils/wizard.h>

namespace Utils { class AbstractMacroExpander; }

namespace ProjectExplorer {

namespace Internal { class JsonWizardExpander; }

class JsonWizardGenerator;

// Documentation inside.
class PROJECTEXPLORER_EXPORT JsonWizard : public Utils::Wizard
{
    Q_OBJECT

public:
    class GeneratorFile {
    public:
        GeneratorFile() : generator(0) { }
        GeneratorFile(const Core::GeneratedFile &f, JsonWizardGenerator *g) :
            file(f), generator(g)
        { }

        bool isValid() const { return generator; }

        Core::GeneratedFile file;
        JsonWizardGenerator *generator;
    };
    typedef QList<GeneratorFile> GeneratorFiles;
    Q_PROPERTY(GeneratorFiles fileList READ fileList)

    explicit JsonWizard(QWidget *parent = 0);
    ~JsonWizard();

    void addGenerator(JsonWizardGenerator *gen);

    Utils::AbstractMacroExpander *expander() const;

    void resetFileList();
    GeneratorFiles fileList();

    QVariant value(const QString &n) const;
    void setValue(const QString &key, const QVariant &value);

    static bool boolFromVariant(const QVariant &v, Utils::AbstractMacroExpander *expander);

    void removeAttributeFromAllFiles(Core::GeneratedFile::Attribute a);

signals:
    void preGenerateFiles(); // emitted before files are generated.
    void postGenerateFiles(const JsonWizard::GeneratorFiles &files); // emitted after files are generated.
    void prePromptForOverwrite(const JsonWizard::GeneratorFiles &files); // emitted before overwriting checks are done.
    void preFormatFiles(const JsonWizard::GeneratorFiles &files); // emitted before files are formatted.
    void preWriteFiles(const JsonWizard::GeneratorFiles &files); // emitted before files are written to disk.
    void postProcessFiles(const JsonWizard::GeneratorFiles &files); // emitted before files are post-processed.
    void filesReady(const JsonWizard::GeneratorFiles &files); // emitted just after files are in final state on disk.
    void allDone(const JsonWizard::GeneratorFiles &files); // emitted just after the wizard is done with the files. They are ready to be opened.

public slots:
    void accept();

private:
    QList<JsonWizardGenerator *> m_generators;

    GeneratorFiles m_files;
    Internal::JsonWizardExpander *m_expander;
};

} // namespace ProjectExplorer

#endif // JSONWIZARD_H
