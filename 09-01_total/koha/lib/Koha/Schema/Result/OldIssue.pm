use utf8;
package Koha::Schema::Result::OldIssue;

# Created by DBIx::Class::Schema::Loader
# DO NOT MODIFY THE FIRST PART OF THIS FILE

=head1 NAME

Koha::Schema::Result::OldIssue

=cut

use strict;
use warnings;

use base 'DBIx::Class::Core';

=head1 TABLE: C<old_issues>

=cut

__PACKAGE__->table("old_issues");

=head1 ACCESSORS

=head2 issue_id

  data_type: 'integer'
  is_nullable: 0

=head2 borrowernumber

  data_type: 'integer'
  is_foreign_key: 1
  is_nullable: 1

=head2 itemnumber

  data_type: 'integer'
  is_foreign_key: 1
  is_nullable: 1

=head2 date_due

  data_type: 'datetime'
  datetime_undef_if_invalid: 1
  is_nullable: 1

=head2 branchcode

  data_type: 'varchar'
  is_nullable: 1
  size: 10

=head2 returndate

  data_type: 'datetime'
  datetime_undef_if_invalid: 1
  is_nullable: 1

=head2 lastreneweddate

  data_type: 'datetime'
  datetime_undef_if_invalid: 1
  is_nullable: 1

=head2 return

  data_type: 'varchar'
  is_nullable: 1
  size: 4

=head2 renewals

  data_type: 'tinyint'
  is_nullable: 1

=head2 auto_renew

  data_type: 'tinyint'
  default_value: 0
  is_nullable: 1

=head2 timestamp

  data_type: 'timestamp'
  datetime_undef_if_invalid: 1
  default_value: current_timestamp
  is_nullable: 0

=head2 issuedate

  data_type: 'datetime'
  datetime_undef_if_invalid: 1
  is_nullable: 1

=head2 onsite_checkout

  data_type: 'integer'
  default_value: 0
  is_nullable: 0

=cut

__PACKAGE__->add_columns(
  "issue_id",
  { data_type => "integer", is_nullable => 0 },
  "borrowernumber",
  { data_type => "integer", is_foreign_key => 1, is_nullable => 1 },
  "itemnumber",
  { data_type => "integer", is_foreign_key => 1, is_nullable => 1 },
  "date_due",
  {
    data_type => "datetime",
    datetime_undef_if_invalid => 1,
    is_nullable => 1,
  },
  "branchcode",
  { data_type => "varchar", is_nullable => 1, size => 10 },
  "returndate",
  {
    data_type => "datetime",
    datetime_undef_if_invalid => 1,
    is_nullable => 1,
  },
  "lastreneweddate",
  {
    data_type => "datetime",
    datetime_undef_if_invalid => 1,
    is_nullable => 1,
  },
  "return",
  { data_type => "varchar", is_nullable => 1, size => 4 },
  "renewals",
  { data_type => "tinyint", is_nullable => 1 },
  "auto_renew",
  { data_type => "tinyint", default_value => 0, is_nullable => 1 },
  "timestamp",
  {
    data_type => "timestamp",
    datetime_undef_if_invalid => 1,
    default_value => \"current_timestamp",
    is_nullable => 0,
  },
  "issuedate",
  {
    data_type => "datetime",
    datetime_undef_if_invalid => 1,
    is_nullable => 1,
  },
  "onsite_checkout",
  { data_type => "integer", default_value => 0, is_nullable => 0 },
);

=head1 PRIMARY KEY

=over 4

=item * L</issue_id>

=back

=cut

__PACKAGE__->set_primary_key("issue_id");

=head1 RELATIONS

=head2 borrowernumber

Type: belongs_to

Related object: L<Koha::Schema::Result::Borrower>

=cut

__PACKAGE__->belongs_to(
  "borrowernumber",
  "Koha::Schema::Result::Borrower",
  { borrowernumber => "borrowernumber" },
  {
    is_deferrable => 1,
    join_type     => "LEFT",
    on_delete     => "SET NULL",
    on_update     => "SET NULL",
  },
);

=head2 itemnumber

Type: belongs_to

Related object: L<Koha::Schema::Result::Item>

=cut

__PACKAGE__->belongs_to(
  "itemnumber",
  "Koha::Schema::Result::Item",
  { itemnumber => "itemnumber" },
  {
    is_deferrable => 1,
    join_type     => "LEFT",
    on_delete     => "SET NULL",
    on_update     => "SET NULL",
  },
);


# Created by DBIx::Class::Schema::Loader v0.07039 @ 2015-04-23 13:04:51
# DO NOT MODIFY THIS OR ANYTHING ABOVE! md5sum:9GdzytyInRcFZns/q0qb3Q


# You can replace this text with custom content, and it will be preserved on regeneration
1;
