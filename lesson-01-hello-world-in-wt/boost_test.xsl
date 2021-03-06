<xsl:for-each select="./TestSuite">
<xsl:variable name="name2" select="@name"/>
<testsuite>
<xsl:attribute name="errors">
<xsl:value-of select="@test_cases_failed" />
/xsl:attribute>
<xsl:attribute name="tests">
<xsl:value-of select="@test_cases_failed + @test_cases_passed + @test_cases_skipped" />
                                                </xsl:attribute>
                                                      <xsl:attribute name="name">
                                                              <xsl:value-of select="@name" />
                                                                    </xsl:attribute>
                                                                          <xsl:for-each select="./TestCase">
<xsl:variable name="name3" select="@name"/>
<testcase>
<xsl:attribute name="name">
<xsl:value-of select="@name" />
</xsl:attribute>
<xsl:for-each select="/xml/TestLog/TestSuite[@name=$name1]">
<xsl:for-each select="./TestSuite[@name=$name2]">
<xsl:for-each select="./TestCase[@name=$name3]">
<xsl:for-each select="./TestingTime">
<xsl:attribute name="time">
<xsl:value-of select="./text() div 100000"/>
</xsl:attribute>
</xsl:for-each>
<xsl:for-each select="./Error">
<failure>
<xsl:attribute name="type">AssertionFailedError</xsl:attribute>
<xsl:attribute name="message">
<xsl:value-of select="@file"/>:<xsl:value-of select="@line"/>
</xsl:attribute>
<xsl:copy-of select="./text()"/>
</failure>
</xsl:for-each>
<xsl:for-each select="./Exception">
<failure>
<xsl:attribute name="type">AssertionFailedException</xsl:attribute>
<xsl:attribute name="message">
<xsl:value-of select="@file"/>:<xsl:value-of select="@line"/>
</xsl:attribute>
<xsl:copy-of select="./text()"/>
</failure>
</xsl:for-each>
<system-out>
<xsl:copy-of select="./text()"/>
</system-out>
</xsl:for-each>
</xsl:for-each>
</xsl:for-each>
</testcase>
</xsl:for-each>
</testsuite>
</xsl:for-each>
</testsuite>
