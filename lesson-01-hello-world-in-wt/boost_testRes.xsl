<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" indent="yes" />
        <xsl:template match="/">
                <report category="test">
                            <xsl:apply-templates />
                                    </report>
                                        </xsl:template>
                                            <xsl:template match="//TestSuite/TestCase">
                                                    <test>
                                                                <status>
                                                                                <xsl:if test="@result = 'passed'">success</xsl:if>
                                                                                                <xsl:if test="@result != 'passed'">failure</xsl:if>
                                                                                                            </status>
                                                                                                                        <fixture><xsl:value-of select="../@name" /></fixture>
                                                                                                                                    <name><xsl:value-of select="@name" /></name>
                                                                                                                                            </test>
                                                                                                                                                </xsl:template>
                                                                                                                                                </xsl:stylesheet>
